#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int int32 ;
struct TYPE_16__ {size_t* DeviceNum; int* ButtonNum; void** ButtType; } ;
struct TYPE_14__ {size_t which; size_t axis; int value; } ;
struct TYPE_13__ {int value; size_t which; int hat; } ;
struct TYPE_12__ {size_t which; int button; } ;
struct TYPE_10__ {int sym; } ;
struct TYPE_11__ {TYPE_1__ keysym; } ;
struct TYPE_15__ {int type; TYPE_5__ jaxis; TYPE_4__ jhat; TYPE_3__ jbutton; TYPE_2__ key; } ;
typedef  TYPE_6__ SDL_Event ;
typedef  TYPE_7__ ButtConfig ;

/* Variables and functions */
 void* BUTTC_JOYSTICK ; 
 void* BUTTC_KEYBOARD ; 
 int SDL_HAT_CENTERED ; 
#define  SDL_JOYAXISMOTION 131 
#define  SDL_JOYBUTTONDOWN 130 
#define  SDL_JOYHATMOTION 129 
#define  SDL_KEYDOWN 128 
 int /*<<< orphan*/  SDL_WM_SetCaption (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ SDL_WaitEvent (TYPE_6__*) ; 
 int abs (int) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/  const*) ; 

int DWaitButton(const uint8 *text, ButtConfig *bc, int wb)
{
 SDL_Event event;
 static int32 LastAx[64][64];
 int x,y;

 SDL_WM_SetCaption(text,0);
 #ifndef EXTGUI
 puts(text);
 #endif
 for(x=0;x<64;x++) 
  for(y=0;y<64;y++)
   LastAx[x][y]=0x100000;

 while(SDL_WaitEvent(&event))
 {
  switch(event.type)
  {
   case SDL_KEYDOWN:bc->ButtType[wb]=BUTTC_KEYBOARD;
		    bc->DeviceNum[wb]=0;
		    bc->ButtonNum[wb]=event.key.keysym.sym;
		    return(1);
   case SDL_JOYBUTTONDOWN:bc->ButtType[wb]=BUTTC_JOYSTICK;
			  bc->DeviceNum[wb]=event.jbutton.which;
			  bc->ButtonNum[wb]=event.jbutton.button; 
			  return(1);
   case SDL_JOYHATMOTION:if(event.jhat.value != SDL_HAT_CENTERED)
			 {
			  bc->ButtType[wb]=BUTTC_JOYSTICK;
			  bc->DeviceNum[wb]=event.jhat.which;
			  bc->ButtonNum[wb]=0x2000|((event.jhat.hat&0x1F)<<8)|event.jhat.value;
			  return(1);
			 }
			 break;
   case SDL_JOYAXISMOTION: 
	if(LastAx[event.jaxis.which][event.jaxis.axis]==0x100000)
	{
	 if(abs(event.jaxis.value)<1000)
 	  LastAx[event.jaxis.which][event.jaxis.axis]=event.jaxis.value;
	}
	else
	{
	 if(abs(LastAx[event.jaxis.which][event.jaxis.axis]-event.jaxis.value)>=8192)
	 {
	  bc->ButtType[wb]=BUTTC_JOYSTICK;
	  bc->DeviceNum[wb]=event.jaxis.which;
	  bc->ButtonNum[wb]=0x8000|(event.jaxis.axis)|((event.jaxis.value<0)?0x4000:0);
	  return(1);
	 }
	}
	break;
  }
 }

 return(0);
}