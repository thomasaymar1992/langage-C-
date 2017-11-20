#include "vrpn_Analog.h"
#include "vrpn_Button.h"

#include <iostream>
using namespace std;
float X,Y;
int ACTIVATED = 1;



void VRPN_CALLBACK handle_analog( void* userData, const vrpn_ANALOGCB a )
{
	X= a.channel[0];
	Y= a.channel[1];

	if(ACTIVATED==1){
		if(X<=0.5 && Y<=0.5){
			printf("zone A");
		}
		else if(X>0.5 && Y<=0.5){
			printf("Zone B");
		}
		else if(X<=0.5 && Y>=0.5){
			printf("Zone C");
		}
		else {
			printf("Zone D");
		}
	} 
}

void VRPN_CALLBACK handle_button( void* userData, const vrpn_BUTTONCB b )
{
	cout << "Button '" << b.button << "': " << b.state << endl;
	if ( (b.button == 2) && (b.state ==1) ){
		Beep(750,300);
		ACTIVATED = 1;
	} 
	if ( (b.button == 1) && (b.state ==1)){
		ACTIVATED = 0;
	}
	else {
		Beep(0,0);
	}
	//	if( (b.button == 1) && (a)
}





int main(int argc, char* argv[])
{
	vrpn_Analog_Remote* vrpnAnalog = new vrpn_Analog_Remote("Mouse0@localhost:3883");
	vrpn_Button_Remote* vrpnButton = new vrpn_Button_Remote("Mouse0@localhost:3883");
	vrpnAnalog->register_change_handler( 0, handle_analog );
	vrpnButton->register_change_handler( 0, handle_button );

	while(1)
	{
		vrpnAnalog->mainloop();
		vrpnButton->mainloop();
		Sleep(100);
	}

	return 0;
}