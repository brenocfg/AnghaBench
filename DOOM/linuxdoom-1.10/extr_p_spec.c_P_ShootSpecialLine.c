#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  player; } ;
typedef  TYPE_1__ mobj_t ;
struct TYPE_10__ {int special; } ;
typedef  TYPE_2__ line_t ;

/* Variables and functions */
 int /*<<< orphan*/  EV_DoDoor (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EV_DoFloor (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EV_DoPlat (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_ChangeSwitchTexture (TYPE_2__*,int) ; 
 int /*<<< orphan*/  open ; 
 int /*<<< orphan*/  raiseFloor ; 
 int /*<<< orphan*/  raiseToNearestAndChange ; 

void
P_ShootSpecialLine
( mobj_t*	thing,
  line_t*	line )
{
    int		ok;
    
    //	Impacts that other things can activate.
    if (!thing->player)
    {
	ok = 0;
	switch(line->special)
	{
	  case 46:
	    // OPEN DOOR IMPACT
	    ok = 1;
	    break;
	}
	if (!ok)
	    return;
    }

    switch(line->special)
    {
      case 24:
	// RAISE FLOOR
	EV_DoFloor(line,raiseFloor);
	P_ChangeSwitchTexture(line,0);
	break;
	
      case 46:
	// OPEN DOOR
	EV_DoDoor(line,open);
	P_ChangeSwitchTexture(line,1);
	break;
	
      case 47:
	// RAISE FLOOR NEAR AND CHANGE
	EV_DoPlat(line,raiseToNearestAndChange,0);
	P_ChangeSwitchTexture(line,0);
	break;
    }
}