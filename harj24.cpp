/**********************************************************
*Tehtävä: Harjoitus24
*Tekijä: Olli Kauppinen
*PVM: 26.11.2013
*Kuvaus:
*Muuta harjoitusta 22 niin, etta valikko nayttaa seuraavalta:
*
*VALIKKO
*0 Lopeta
*1 Lisaa henkilo
*2 Nayta henkilo
*3 Nayta kaikki henkilot
*4 Poista henkilon tiedot
*5 Tallenna tiedot tiedostoon
*6 Hae tiedot tiedostosta
*
*
*ja toteuta valikossa näkyvät toiminnot.
*
*Valitse haluamasi tallennusformaatti.
*
* Versio 1.0 H4718 26.11.2013
***********************************************************/

#include <iostream>
#include <fstream>
using namespace std;



struct TIEDOT
{
	char nimi[20];
	float kmatka;
	int hat;
};

const int MAX_TAULU = 10;

int Valikko(void);
void TulostaKaikkiTIEDOT(TIEDOT hlo[], int lkm);
void LisaaHenkilo(TIEDOT [], int *lkm);
void TulostaHenkilo(TIEDOT hlo[]);
void PoistaHLO(TIEDOT hlo[], int *hlo_lkm);
void TallennaTiedostoon(TIEDOT hlo[], int lkm);
void HaeTiedostosta(TIEDOT [], int *lkm);

int main()
{
	int valinta = 0;
	int lkm = 0;
	bool jatka = true;
	TIEDOT hlo[MAX_TAULU];
	

	do
	{
		cout << "\nHenkiloita rekisterissa " << lkm << " kpl" << endl;
		cout << "Max. 10 kpl." << endl;
		valinta = Valikko();
		cout << endl;

		switch (valinta)
		{
			case 0:
			{
				cout << "\nGood bye.\n";
				jatka = false;
				break;
			}

			case 1:
			{
				if (lkm < 10)
				{
				LisaaHenkilo(hlo, &lkm);
				}
				
				else
				{
				cout << "Taulukko taysi!" << endl;
				}
				break;
			}

			case 2:
			{
				TulostaHenkilo(hlo);
				break;
			}

			case 3:
			{

				TulostaKaikkiTIEDOT(hlo, lkm);

				break;
			}

			case 4:
			{
				PoistaHLO(hlo, &lkm);

				break;
			}

			case 5:
			{
				TallennaTiedostoon(hlo, lkm);

				break;
			}

			case 6:
			{
				HaeTiedostosta(hlo, &lkm);

				break;
			}

			default:
			{
				cout << "\nVaara valinta\n";
				break;
			}

		}
	}

	while (jatka == true);

}

int Valikko(void)
{
	int valinta;

	cout << "\nVALIKKO\n\n0 Lopeta\n1 Lisaa henkilo\n2 Tulosta hlo\n3 Tulosta kaikki" << endl;
	cout << "4 Poista henkilon tiedot\n5 Tallenna tiedostoon\n6 Hae tiedostosta" << endl;
	cin >> valinta;

	return valinta;
}

void TulostaKaikkiTIEDOT(TIEDOT hlo[],int lkm)
{
	cout << "Listaus:" << endl;
	for (int ind = 0; (ind < lkm); ind++)
	{
		cout << ind+1 << ". Nimi: " << hlo[ind].nimi << ", koulumatka: " << hlo[ind].kmatka << " km, hatun koko: " << hlo[ind].hat << endl;
	}
}

void LisaaHenkilo(TIEDOT p_hlo[], int *hlo_lkm)
{
	cout << "\nEtunimi?\n";
	cin >> p_hlo[*hlo_lkm].nimi;
	cout << "\nKoulumatka?\n";
	cin >> p_hlo[*hlo_lkm].kmatka;
	cout << "\nHatun koko?\n";
	cin >> p_hlo[*hlo_lkm].hat;

	(*hlo_lkm)++;
}

void TulostaHenkilo(TIEDOT p_hlo[])
{
	int nro;
	cout << "Henkilo nro? " << endl;
	cin >> nro;
	if (nro > 10)
	{
		cout << "Valinta ei mahdollinen, max maara 10" << endl;

	}
	else
	{
	 cout << "Nimi: " << p_hlo[nro-1].nimi << ", koulumatka: " << p_hlo[nro-1].kmatka << " km, hatun koko: " << p_hlo[nro-1].hat << endl;
	}
}

void PoistaHLO(TIEDOT p_hlo[], int *hlo_lkm)
{
	int nro;

	cout << "Valitse poistettava henkilo: " << endl;
	cin >> nro;

	*p_hlo[nro-1].nimi = NULL;
	p_hlo[nro-1].kmatka = 0;
	p_hlo[nro-1].hat = 0;

	for (nro; nro <= *hlo_lkm; nro++)
	{
		p_hlo[nro-1] = p_hlo[nro];
	}

	(*hlo_lkm)--;
}

void TallennaTiedostoon(TIEDOT hlo[], int lkm)
{
	ofstream tdsto("tiedot.csv");

	tdsto << "HLO.NRO; NIMI; KOULUMATKA; HATTU" << endl;

	for (int ind = 0; (ind < lkm); ind++)
	{
		tdsto << ind+1 << ';' << hlo[ind].nimi << ';' << hlo[ind].kmatka << ';' << hlo[ind].hat << endl;
	}
}

void HaeTiedostosta(TIEDOT p_hlo[], int *hlo_lkm)
{
	char otsikko[40];
	int ind = 0;
	int nro;
	ifstream lue("tiedot.csv");

	lue.getline(otsikko, 40);

	do
	{
		lue >> nro;
		lue.get();
		lue.get(p_hlo[ind].nimi, 20, ';');
		lue.get();
		lue >> p_hlo[ind].kmatka;
		lue.get();
		lue >> p_hlo[ind].hat;
		lue.get();
		ind++;
		
		
	}
	while (lue.good());

	(*hlo_lkm) = ind-1;
	lue.close();
}