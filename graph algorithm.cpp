/*
 * graph algorithm.cpp
 *
 *  Created on: 15-Jul-2018
 *      Author: indrajeet
 */
#include<iostream>
#include<climits>
#include<fstream>
#include<iterator>
#include<vector>
using namespace std;
template<class T>
class graph{
private :
	int V,E;
	T **weight;
public:
	graph(int v=0,int e=0):V(v),E(e){
		cout << "constructor is called" <<endl;
		weight = new T*[V];
		for(int i=0;i<V;i++)
			weight[i] = new T[V];
	}
	~graph(){
		cout << "Destructor is called" <<endl;
		for(int i=0;i<V;i++)
			delete [] weight[i];
	}
	void readGraph();
	void printGraph();
	bool isConnected();
	T dijkstraAlgo(int,int);
	T minimumSpanningTree(int);
};
template<class T>
void graph<T>::readGraph(){
	ifstream input;
	input.open("src/graph.txt");
	istream_iterator<int> start(input),end;
	vector<int> data(start,end);
	if(!input.is_open())
		cout << "Input file could not be opened! Terminating!"<<endl;
	else{
		int row=0,col=0;
		for(int d:data){
			if(d==0 && row !=col)
				weight[row][col]=INT_MAX;
			else
				weight[row][col] = d;
			if(col == V-1)
				row++;
			col=(col+1)%V;
		}
	}
	input.close();
}
template<class T>
void graph<T>::printGraph(){
	for(int i=0;i<V;i++){
		for(int j=0;j<V;j++)
			if (weight[i][j]==INT_MAX)
				cout << '0' << " ";
			else
				cout << weight[i][j] <<" ";
		cout <<endl;
	}
}
template<class T>
bool graph<T>::isConnected(){
	bool *connected = new bool[V];
	for(int i=0;i<V;i++)
		connected[i]=false;
	connected[0]=true;
	for(int i=0;i<V;i++)
		if(connected[i]==true)
			for(int j=0;j<V;j++)
				if(connected[j]==false && weight[i][j]!=0)
					connected[j]=true;
	for(int i=0;i<V;i++)
		if(connected[i]==false){
			cout << "Graph is disconnected" <<endl;
			return false;
		}
	cout << "Graph is connected" <<endl;
	return true;
}
template<class T>
int findmin(T *dist,bool *isVisited,int size){
	int min = INT_MAX,index=0;
	for(int i=0;i<size;i++)
		if(isVisited[i]==false && min > dist[i]){
			min = dist[i];
			index=i+1;
		}
	isVisited[index-1]=true;
	return index;
}
template<class T>
T graph<T>::dijkstraAlgo(int source,int destination){
	T *minDist = new T[V];
	bool *isVisited = new bool[V];
	for(int i=0;i<V;i++){
		minDist[i]=INT_MAX;
		isVisited[i]=false;
	}
	minDist[source]=0;
	int i;
	while((i=findmin(minDist,isVisited,V))!=0)
		for(int j=0;j<V;j++)
			if(long(minDist[i-1])+weight[i-1][j] < minDist[j])
				minDist[j] = minDist[i-1]+weight[i-1][j];
	int dist =minDist[destination];
	//delete [] minDist;
	//delete [] isVisited;
	return dist;
}
template<class T>
T graph<T>::minimumSpanningTree(int source){
	T *minDist = new T[V];
	bool *isVisited = new bool[V];
	int *parent = new int[V];
	for(int i=0;i<V;i++){
		minDist[i]=INT_MAX;
		isVisited[i]=false;
		parent[i]=-1;
	}
	minDist[source]=0;
	parent[source]=0;
	int i;
	while((i=findmin(minDist,isVisited,V))!=0)
		for(int j=0;j<V;j++)
			if(isVisited[j]==false && weight[i-1][j] < minDist[j]){
				minDist[j] = weight[i-1][j];
				parent[j] = i-1;
			}
	cout <<"Node  "<<"Dist  "<<"Parent"<<endl;
	T sum=0;
	for(int j=0;j<V;j++){
		cout << j <<"     "<<minDist[j]<<"     "<<parent[j]<<endl;
		sum+=minDist[j];
	}
	delete [] minDist;
	return sum;
}
int main(void){
	graph<int> g(9);
	g.readGraph();
	g.printGraph();
	g.isConnected();
	cout << "Min Distance B/W 0 to 4 :" <<g.dijkstraAlgo(0,4)<<endl;
	cout<<g.minimumSpanningTree(0)<<endl;
	return 0;
}




