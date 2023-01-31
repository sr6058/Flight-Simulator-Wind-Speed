//***********************************************************//
//** Author: Smriti Ramachandran **
//** Date Created: October 22, 2021 **//
//** Assignment 2: Flight Simulator Wind Speed **//
//** UH-1000 Computer Programming for Engineers, NYUAD **//
//** Problem: **//
//** To generate a computer simulation of wind speed for a flight simulator **//
//***********************************************************//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#define MAX 50 // size of the array
using namespace std;

//function prototypes
void windspeedData(double avgspeed, double gust, double duration, double step,double windspeed_data[]);
void generatesStormData(double stprob, double  minsampl , double  maxsampl , double  minsdur , double maxsdur, double stormdata[],double duration,double step);
void generateBurstData(double microprob, double minbampl, double maxbampl, double minbdur, double maxbdur, double duration, double microburstdata[],double step,double stormdata[]);
void generateWindSimulation(double microburstdata[], double stormdata[], double windspeed_data[], double duration, double step, double final_wind_sim[]);

int main()
{
	//Input variables
	double avgspeed = 0, gust = 0, duration = 0, step = 0;
	double stprob = 0,  minsampl = 0,  maxsampl = 0,  minsdur = 0,  maxsdur = 0;
	double microprob = 0,  minbampl = 0, maxbampl = 0, minbdur = 0, maxbdur = 0;
	
	//Declaration of Arrays
	double windspeed_data[MAX];
	double stormdata[MAX];
	double microburstdata[MAX];
	double final_wind_sim[MAX];

	//Reading values from simulationConfiguration.txt into variables
	ifstream in;
	in.open("simulationConfiguration.txt", ios::in);
	if (in.fail())
	{
		cerr << "Error opening the file" << endl;
		exit(-1);
	}
	in >> avgspeed >> gust >> duration >> step;
	in >> stprob >> minsampl >> maxsampl >> minsdur >> maxsdur;
	in >> microprob >> minbampl >> maxbampl >> minbdur >> maxbdur;
	
	in.close();

	//Calling functions from main
	windspeedData(avgspeed, gust, duration, step, windspeed_data);
	
	generatesStormData(stprob , minsampl ,  maxsampl ,  minsdur, maxsdur, stormdata,duration,step);
	
	generateBurstData(microprob, minbampl, maxbampl, minbdur, maxbdur, duration, microburstdata,step,stormdata);
	
	generateWindSimulation(microburstdata, stormdata, windspeed_data, duration, step, final_wind_sim);
	
}

void windspeedData(double avgspeed, double gust, double duration, double step,double windspeed_data[])
{
	ofstream outFile;
	outFile.open("WindSpeedData.txt", ios::out);
	srand((unsigned int)time(NULL));

	if (outFile.fail())
	{
		cerr << "Error creating the file\n";
		exit(-1);
	}
	outFile << setw(10) << left << "Windspeed" << setw(10) << left << "Time" << endl;
	double a, b;
	a = avgspeed - gust;
	b = avgspeed + gust;
	double data(0);
	int x = 0;
	//random windspeeds generated for duration given
	for (int i(0) ;i < duration; i+= step)
	{
		data = ((double)rand() / RAND_MAX) * (b - a) + a;
		outFile << setw(10)<<left<<data <<setw(10)<<left <<i << endl;
		windspeed_data[x] = data; //windspeed values stored in array windspeed_data[]
		x++;
	}
	outFile.close();

	
}


void generatesStormData(double stprob , double  minsampl , double  maxsampl , double  minsdur , double maxsdur, double stormdata[],double duration,double step )
{
	srand((unsigned int)time(NULL));

	ofstream outFile;
	outFile.open("StormData.txt", ios::out);
	if (outFile.fail())
	{
		cerr << "Error creating the file\n";
		exit(-1);
	}
	double randomnumber;
	double stmag(0);
	double time;
	
	for (int j(0);j < duration;j+=step)
	{
		
		
		randomnumber = ((double)rand() / RAND_MAX) * (100 - 0) + 0;
		if (randomnumber < stprob) //probabilty that the storm occurs
		{
			time = ((double)rand() / RAND_MAX) * (maxsdur - minsdur) + minsdur;
			stmag = ((double)rand() / RAND_MAX) * (maxsampl - minsampl) + minsampl;
			int i;
			//for a duration of randomly generated time a constant magnitude is outFiled
			for (i=j;i < j+time;i += step)
			{
				outFile << setw(10) << left << stmag << setw(10) << left << i << endl;
			}
		
		j = i-2;
		}
		else //when storm doesn't occur
		{
			outFile <<setw(10)<<left<< 0 <<setw(10)<<left<< j << endl;
		}

	}
	outFile.close();

	//Opening file for reading value into array
	int i = 0;
	double dummy[MAX];
	ifstream in;
	in.open("StormData.txt", ios::in);
	if (in.fail())
	{
		cerr << "Error opening the file" << endl;
		exit(-1);
	}
	while (i<20)
	{
		in >> stormdata[i] >> dummy[i]; //stormdata[] stores values of windspeeds when the storm occurs or doesn't occur
		i++;
	}
	in.close();
}

void generateBurstData(double microprob, double minbampl, double maxbampl, double minbdur, double maxbdur, double duration,double microburstdata[], double step, double stormdata[])
{
	srand((unsigned int)time(NULL));
	ofstream outFile;
	outFile.open("BurstData.txt", ios::out);
	if (outFile.fail())
	{
		cerr << "Error creating the file\n";
		exit(-1);
	}
	double randomnumber;
	double bampl(0);
	double time;
	int x = 0;
	
	for (int j(0);j < duration;j+=step)
	{
		
		randomnumber = ((double)rand() / RAND_MAX) * (100 - 0) + 0;
		if (stormdata[x] != 0) //to check whether storm occurs, as microburst can occur only when there is a storm
		{
			if (randomnumber < microprob)//to check whether there is a probability for the microburst to occur
			{
				time = ((double)rand() / RAND_MAX) * (maxbdur - minbdur) + minbdur;
				bampl = ((double)rand() / RAND_MAX) * (maxbampl - minbampl) + minbampl;
				int i;
				for (i=j;i < j+time;i+=step)
				{
					outFile << setw(10)<<left <<bampl << setw(10)<<left << i<< endl;
				
				}
				j = i-2;
			}
			else //microburst doesn't occur
			{
				outFile << setw(10)<<left<<0<< setw(10)<<left<< j<< endl;
			}
		}
		else // neither storm nor microburst occurs
		{
		   outFile << setw(10)<<left<<0<< setw(10)<<left<< j << endl;
		}
		x++;
	}
	outFile.close();
	//opening file for reading value into array microburstdata[]
	int i = 0;
	double dummy[MAX];
	ifstream in;
	in.open("BurstData.txt", ios::in);
	if (in.fail())
	{
		cerr << "Error opening file" << endl;
		exit(-1);
	}
	while (i<20)
	{
		in >> microburstdata[i] >> dummy[i];
		i++;
	}
	in.close();
}


void generateWindSimulation(double microburstdata[], double stormdata[], double windspeed_data[],double duration,double step, double final_wind_sim[])
{
	ofstream outFile;
	int x = 0;
	outFile.open("WindSimulation.txt", ios::out);
	if (outFile.fail())
	{
		cerr << "Error creating the file\n";
		exit(-1);
	}
	outFile << setw(30) << left << "Final Windspeed" << setw(30) << left << "Time" << setw(30) << left << "Storm occurrence" << endl;
	for (int i(0);i < duration; i+=step)
	{
		final_wind_sim[x] = microburstdata[x] + stormdata[x] + windspeed_data[x]; //adds windspeed from each array at a specific time and stores in final_wind_sim[]
		outFile << setw(30) << left << final_wind_sim[x] << setw(30) << i; //outFile final windspeed values into WindSimulation.txt
		if (stormdata[x] == 0)
		{
			outFile << setw(30) << left << 0 << endl; //binary value 0 when the storm doesn't occur
		}
		else
		{
			outFile << setw(30) << left << 1 << endl; //binary value 1 when the storm occurs
		}
		x++;
	}
	outFile.close();
}
