#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <bitset>
#include <algorithm>//for unique and distance

using namespace std;
string hextobinstring(string input)
{
	string sReturn = "";
			for (int i = 0; i < input.length (); ++i)
			{
				switch (input [i])
				{
					case '0': sReturn.append ("0000"); break;
					case '1': sReturn.append ("0001"); break;
					case '2': sReturn.append ("0010"); break;
					case '3': sReturn.append ("0011"); break;
					case '4': sReturn.append ("0100"); break;
					case '5': sReturn.append ("0101"); break;
					case '6': sReturn.append ("0110"); break;
					case '7': sReturn.append ("0111"); break;
					case '8': sReturn.append ("1000"); break;
					case '9': sReturn.append ("1001"); break;
					case 'a': sReturn.append ("1010"); break;
					case 'b': sReturn.append ("1011"); break;
					case 'c': sReturn.append ("1100"); break;
					case 'd': sReturn.append ("1101"); break;
					case 'e': sReturn.append ("1110"); break;
					case 'f': sReturn.append ("1111"); break;
				}
			}
			return sReturn;
}
int main()
{
	ifstream file("D:/Computer architecture/assignment3/hwtrace(2).out");
	ofstream file2("D:/Computer architecture/assignment3/key.doc");
	ofstream file3("D:/Computer architecture/assignment3/twocounter.doc");
	vector<string> line;vector<string> branch;
	string i;long long int diff,diff1;long long int a1,a11;long long int a2,a21;
	if(file.is_open())
	{
		while(getline(file,i))
		line.push_back(i);
	}
	cout<<"number of  instructions in itrace:";
	cout<<line.size()<<endl;
	int size=line.size();//size declaration and initialization
	for(int i=0;i<size-1;i++)
	{
		a1=stoll(line[i+1],nullptr,16);
		a2=stoll(line[i],nullptr,16);
		diff=a1-a2;
		if(diff>15 || diff<0)
		{
			branch.push_back(line[i]);
		}
	}
	cout<<"number of branch instructions in itrace:";
	cout<<branch.size()<<endl;	
	sort(branch.begin(),branch.end());
	branch.erase(unique(branch.begin(),branch.end()),branch.end());
	cout<<"number of unique branch instructions:";
	cout<<branch.size()<<endl;
	map<string,int> dec;//map declaration
	string key;//Key-declaration
	string b3;//b3 declared to store converted version
	int length;//length declared to store the length of the binary string version
	int pre=0,mpre=0;//pre(prediction) and mpre(misprediction) declarations
	for(int i=0;i<branch.size();i++)
	{
		b3=hextobinstring(branch[i].substr(2));
		length=b3.length();
		while(length!=48)
		{
			b3="0000"+b3;
			length=length+4;
		}
		key=b3.substr(43);
		file2<<branch[i]<<"substring: "<<branch[i].substr(2)<<"| binary: "<<b3<<"| length: "<<b3.length()<<"| key "<<key<<endl;
		dec[key]=1;
	}
	file2.close();
	map<string,int>::iterator itmap;
	for(int i=0;i<line.size()-1;i++)
	{
		for(int j=0;j<branch.size();j++)
		{
			a11=stoll(line[i+1],nullptr,16);
			a21=stoll(line[i],nullptr,16);
			diff1=a11-a21;
			b3=hextobinstring(line[i].substr(2));
			length=b3.length();
			while(length!=48)
			{
				b3="0000"+b3;
				length=length+4;
			}
			key=b3.substr(43);
			//int compar=strcmp(branch[j],line[i]);
			if(branch[j]==line[i])
			{
				if(diff1>15||diff1<0)
				{
					if(dec[key]==1)
						pre++;
					else
					{
						mpre++;
						dec[key]=1;
					}
				}
				else
				{
					if(dec[key]==0)
					{
						pre++;
					}
					else
					{
						mpre++;
						dec[key]=0;
					}
				}
			}		
		}
	}
	cout<<"Number of correct predictions:";
	cout<<pre<<endl;
	cout<<"Number of mis-predictions:";
	cout<<mpre<<endl;
	cout<<"hash table"<<endl;
	for(itmap=dec.begin();itmap!=dec.end();itmap++)
	{
		cout<<itmap->first<<":"<<itmap->second<<endl;
	}
	//----TWO BIT COUNTER----//
	map<string,int> dic;//hash table declaration for 2 bit counter
	string b32;
	string key2; int pre2=0,mpre2=0;long long int diff2bit;
	for(int i=0;i<branch.size();i++)
	{
		b32=hextobinstring(branch[i].substr(2));
		length=b32.length();
		while(length!=48)
		{
			b32="0000"+b32;
			length=length+4;
		}
		key2=b32.substr(44);
		file3<<branch[i]<<"substring: "<<branch[i].substr(2)<<"| binary: "<<b32<<"| length: "<<b32.length()<<"| key "<<key2<<endl;
		dic[key2]=1;
	}
	file3.close();
	for(int i=0;i<line.size()-1;i++)
	{
		for(int j=0;j<branch.size();j++)
		{
			diff2bit=stoll(line[i+1],nullptr,16)-stoll(line[i],nullptr,16);
			if(branch[j]==line[i])
			{
				b32=hextobinstring(branch[j].substr(2));
				length=b32.length();
				while(length!=48)
				{
					b32="0000"+b32;
					length=length+4;
				}
				key2=b32.substr(44);
				if(diff2bit>15 || diff2bit<0)
				{
					if(dic[key2]==0)
					{
						mpre2++;
						dic[key2]=1;
					}
					else if(dic[key2]==1)
					{
						mpre2++;
						dic[key2]=3;
					}
					else if(dic[key2]==2)
					{
						pre2++;
						dic[key2]=3;
					}
					else if(dic[key2]==3)
					{
						pre2++;
						dic[key2]=3;
					}
				}
				else
				{
					if(dic[key2]==0)
					{
						pre2++;
						dic[key2]=0;
					}
					else if(dic[key2]==1)
					{
						pre2++;
						dic[key2]=0;
					}
					else if(dic[key2]==2)
					{
						mpre2++;
						dic[key2]=0;
					}
					else if(dic[key2]==3)
					{
						mpre2++;
						dic[key2]=2;
					}
				}
			}
		}
	}
	cout<<"Number of correct predictions(2bitcounter):";
	cout<<pre2<<endl;
	cout<<"Number of mis-predictions(2bitcounter):";
	cout<<mpre2<<endl;
	cout<<"hash table(2bit counter)"<<endl;
	for(itmap=dic.begin();itmap!=dic.end();itmap++)
	{
		cout<<itmap->first<<":"<<itmap->second<<endl;
	}
	return 0;
}
