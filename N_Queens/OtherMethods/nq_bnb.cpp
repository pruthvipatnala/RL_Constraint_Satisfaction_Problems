#include<iostream>
#include<queue>
#include<cmath>
#include<vector>
#include<fstream>
#include<sstream>
using namespace std;
 
int count = 0;

 //Define a node class
struct Node{
	int number;
	 vector<int>x;//Save the current solution 
}; 
 
 //Define a Queen class 
class Queen{
	friend int nQueen(int);
	public:
		bool Place(Node q,int n);
		void Research();
		 int n;//Queens
		 int *bestx;//Optimal solution
}; 
 
 //The function to determine whether it can be placed 
bool Queen::Place(Node q,int n)
{
	for(int j=1;j<n;j++)
	  if((abs(n-j)==abs(q.x[j]-q.x[n]))||(q.x[j]==q.x[n])) return false;
	
	return true;
}
 
void Queen::Research()
{
	 queue<Node>Q;//Living node queue
	Node sign;
	sign.number=-1;
	 Q.push(sign);//The tail sign of the node on the same layer
	 int t=1;//The layer where the current node is
	 Node Ew;//Current expansion node 
	Ew.number=0; 
	 //Search subset space tree
	while(1){	
	    //Check all child nodes 
	   for(int k=1;k<=n;k++){
		 //Assign the value of the current extended node to the next node 
		Node q;
	        q.number=t; 
	         q.x.push_back(0);//The first position is 0 
    	        for(int i=1;i<t;i++) q.x.push_back(Ew.x[i]);
    	        q.x.push_back(k);
		if(Place(q,t)) {
			count++;
			Q.push(q);
		}
    	    }	 
		 //Take the next extended node, take it out, and assign it to Ew 
		Ew=Q.front();
		Q.pop();
		if(Ew.number==-1){
		     //Tail marker at the same layer
		     t++;//Enter the next layer 
		     Q.push(sign);//Add mark
		     //Continue to the next node 
		    Ew=Q.front();
		    Q.pop();
		}		
		 if(Ew.number==n){//Find the node of the last layer 
		   for(int i=0;i<=n;i++) bestx[i]=Ew.x[i];
		   break;
		} 
	}
}
 
int nQueen(int n,ofstream &outfile)
{
	Queen X;
	X.n=n;	
	X.bestx=new int[n+1];
	for(int i=0;i<=n;i++) X.bestx[i]=0;
	X.Research();
	for(int i=1;i<=n;i++){
		outfile<<X.bestx[i]<<" ";
	}
}
 

int main(){
	
	int N = 4;
	
	ofstream outfile;
	outfile.open("output.txt",ios::out);
	
	nQueen(N,outfile);
	
	outfile.close();
	cout << count << endl;
	return 0;
}
