#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int NumC; scalar_t__* ButtType; size_t* ButtonNum; } ;
typedef  TYPE_1__ ButtConfig ;

/* Variables and functions */
 scalar_t__ BUTTC_JOYSTICK ; 
 scalar_t__ BUTTC_KEYBOARD ; 
 scalar_t__ DTestButtonJoy (TYPE_1__*) ; 
 scalar_t__* KeyState ; 

int DTestButton(ButtConfig *bc)
{
 int x;

 for(x=0;x<bc->NumC;x++)
 {
  if(bc->ButtType[x]==BUTTC_KEYBOARD)
  {
   if(KeyState[bc->ButtonNum[x]])
    return(1);
  }
  else if(bc->ButtType[x]==BUTTC_JOYSTICK)
  {
   if(DTestButtonJoy(bc))
    return(1);
  }
 }
 return(0);
}