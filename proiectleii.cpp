#include <iostream>
#include <fstream>
//#include <sstream>
#include <string>
#include <time.h>
//#include <stdio.h>

#define SPEED std
#define nrFig 132
#define pretAuto 5680
#define Dolar 4.4
using namespace SPEED;

//randomizarea puliii

template <typename rnd>
rnd random(rnd var)
{
	return rand() % var;
}

class RANDOM
{
public:
	string monstrii[5] = { "pula", "pizda","gaoaza", "tate", "muie" };
	string mancare[3] = { "straight", "gay", "tigaie" };
	// RETURN RANDOM STRING DIN MANCARE
	string randomMat(string s[3])
	{
		return s[random(3)];
	}
	// RETURN RANDOM STRING DIN MACHIAJ
	string randomRol(string s[5])
	{
		return s[random(5)];
	}
	// RETURN RANDOM STRING DIN CELE 2X 1000 NUME PT FIGURANTI + CONCATENARE
	string randomFiguri(string nume1[1000], string nume2[1000], int nr)
	{
		return nume1[random(nr)] + " " + nume2[random(nr)];
	}
};

class Database
{
public:
	string c1[1000];
	string c2[1000];
	int nrCast = 0;
	int nrActori = 0;
	~Database();
};
Database::~Database(void) {} //destructor


//clasa de citire din csv init
class Citire_CSV
{
public:
	int citire_init_CSV(string coloana1[1000], string coloana2[1000], string filename) //am doua coloane in csv
	{
		ifstream file0;
		file0.open(filename);

		char delim1(',');
		char delim2('\n');

		int contor = 0;//pt indexare

		try
		{
			if (!file0.is_open()) //in caz de eroare si  nu-mi deschide file
				throw '1';
			else
			{
				while (!file0.eof())
				{
					getline(file0, coloana1[contor], delim1);
					getline(file0, coloana2[contor], delim2);
					contor++;

				}
				contor--; //testare
				return contor;
			}
		}
		catch (char error)
		{
			if (error == '1')
			{
				cout << "EROARE FATALA" << endl;
				return 0;
			}
		}

	}
	~Citire_CSV();
};
Citire_CSV::~Citire_CSV(void) {}


void testare_scriere(int contor, string coloana1[1000], string coloana2[1000])
{
	for (int i = 0; i < contor; i++)
	{
		cout << i + 1 << "} ";
		cout << coloana1[i] << " - ";
		cout << coloana2[i] << endl;
	}
}

class Scriere_CSV

{
public:
	int scriereCSV1(string coloana1[1000], string coloana2[1000], int nrCast)
	{
		RANDOM rnd;
		string nume1[1000];
		string nume2[1000];
		Citire_CSV citire1;
		
		int contornume=citire1.citire_init_CSV(nume1, nume2, "names.csv");
		//testare_scriere(contornume, nume1, nume2);
		ofstream data_base_writer;

		data_base_writer.open("desfasurator.csv");

		char delim1(',');
		char delim2('\n');

		int ncActori=0;
		try
		{
			if (!data_base_writer.is_open())
				throw '1';
			else
			{
				cout << ">> Scriere in fisier actori..." << endl;
				// SCRIERE DOAR ACTORI DIN CSV INITIAL IN NOUL CSV + ROL/DIETA GENERATE RANDOM
				for (unsigned int i = 0; i < nrCast; i++)
				{
					if (coloana2[i].find("actor/actress") != string::npos)
					{
						data_base_writer << coloana1[i];
						data_base_writer << delim1;
						data_base_writer << "actor";
						data_base_writer << delim1;
						data_base_writer << rnd.randomMat(rnd.mancare); //data_base_write<<"CIBO";
						data_base_writer << delim1;
						data_base_writer << rnd.randomMat(rnd.monstrii); //data_base_write<<"RUOLO";
						data_base_writer << delim2;
						ncActori++;
					}
				}
				cout << ">> Scriere in fisier figuranti..." << endl;
				for (unsigned int i = 0; i < nrFig; i++)
				{
					data_base_writer << rnd.randomFiguri(nume1, nume2, nrFig);
					data_base_writer << delim1;
					data_base_writer << "Figurant";
					data_base_writer << delim2;
					//data_base_writer << rnd.rndMancare(ranStrGen.mancare);
					//data_base_writer << delim2;

					//data_base_writer << ranStrGen.rndRol(ranStrGen.rol);
					//data_base_writre << delim2;
				}
				cout << ">> Scriere in fisier restul cast-ului..." << endl;
				// SCRIERE DIN VECHIUL CSV IN NOUL CSV RESTUL CASTULUI
				for (unsigned int i = 0; i < nrCast; i++)
				{
					if (coloana2[i].find("actor/actress") == string::npos)

					{
						data_base_writer << coloana1[i];
						data_base_writer << delim1;

						data_base_writer << coloana2[i];
						data_base_writer << delim2;
					}
				}
					data_base_writer.close();
			}
		}
		catch (char error)
		{
			if (error == '1')
			{
				cout << "erorica fatalica" << endl;
				return 0;
			}


		}
		return ncActori;
	}
	
};

void preScriereCSV2()
{
	ofstream data_base_write;
	data_base_write.open("castprices.csv");
	char delimeter1(',');           // delimitator
	char delimeter2('\n');
	try
	{
		if (!data_base_write.is_open())
			throw '1';
		else
		{
			data_base_write << "Zile";    data_base_write << delimeter1;
			data_base_write << "30";      data_base_write << delimeter1;
			data_base_write << "45";      data_base_write << delimeter1;
			data_base_write << "60";      data_base_write << delimeter1;
			data_base_write << "100";     data_base_write << delimeter2;
		}
	}
	catch (char error)
	{
		if (error == '1')
		{
			cout << ">> Whops, a intervenit o eroare in scrierea fisierului CSV." << endl;
			cout << ">> Va rugam verificati integritatea fisierului si redeschideti aplicatia." << endl;
		}
	}
}

void contScriereCSV2(unsigned int price[4], string sInput) //asta e in continuare
{
	ofstream continuare;

	continuare.open("castprices.csv", ios::app);
	char delimiter1(',');
	char delimiter2('/n');

	continuare.open("castprices.csv", ios::app);
	char delimeter1(';');           // DELIMITATORI PENTRU FISIERUL CSV
	char delimeter2('\n');
	try
	{
		if (!continuare.is_open())
			throw '1';
		else
		{
			continuare << sInput;
			continuare << delimeter1;
			for (unsigned int i = 0; i < 3; i++)
			{

				continuare << price[i];
				continuare << delimeter1;
			}
			continuare << price[3];
			continuare << delimeter2;
		}
	}
	catch (char error)
	{
		if (error == '1')
		{
			cout << ">> VAI, NU SE DESCHIDE ." << endl;
			cout << ">> MAI INCEACRCA." << endl;
		}
	}

}


//clasa initiala de la care pornesc apoi in alta separata pentru cost parinteeeee
class Membrii
{
protected:
	unsigned int nrCast0;
	unsigned int nrActori;

public:
	Membrii();
	Membrii(int nrCast, int nrActor)
	{
		nrCast0 = nrCast;
		nrActori = nrActor;

	}
	unsigned int getNrCast()
	{
		return this->nrCast0;
	}
	unsigned int getNrActor()
	{
		return this->nrActori;
	}
	~Membrii();
};



//clasa de mosteneste de mai sus

class Preturi : private Membrii
{

private:
	unsigned int pretAutocar[4];
	unsigned int pretCazare[4];
	unsigned int pretMonstrii[4];
	unsigned int pretChirie[4];

	unsigned int pretHaleala[4];

	unsigned int Perioada[4] = { 30, 45, 60, 100 };
	unsigned int nrzile;

public:
	Preturi(unsigned int nrCast, unsigned int nrActor) :Membrii(nrCast, nrActor)
	{
		nrCast0 = nrCast;
		nrActori = nrActori;
		cout << "Generam fisier legat de COSTURI ALE DREQ" << endl << endl;


	}
	Preturi();


	//calculam preturile and shit AUTOCARE

	//getch();

	void getPretAuto()
	{
		unsigned int Total = nrCast0 + nrFig;
		pretAutocar[0] = Total / 50;
		if (Total % 50 != 0)
			pretAutocar[0]++;
		pretAutocar[0] = pretAutocar[0] * pretAuto * 2 / Dolar;


		for (unsigned int i = 1; i < 4; i++)
			pretAutocar[i] = pretAutocar[0];
		
		
		contScriereCSV2(pretAutocar, "$ AUTO");
		//scriere in fis
	}
};




int main()
{
	srand(time(NULL));

	Database cast;

	Citire_CSV citire0;

	cast.nrCast = citire0.citire_init_CSV(cast.c1, cast.c2, "wednesdayCast.csv");
	cast.nrActori = citire0.citire_init_CSV(cast.c1, cast.c2, "wednesdayCast.csv");
	//testare_scriere(cast.nrCast, cast.c1, cast.c2);
	Scriere_CSV scriere0;
	scriere0.scriereCSV1(cast.c1, cast.c2, cast.nrCast);

	Membrii membrii(cast.nrCast, cast.nrActori);
	Preturi preturi(membrii.getNrCast(), membrii.getNrActor());
	preScriereCSV2();
	
	
	preturi.getPretAuto();
	return 0;
}
