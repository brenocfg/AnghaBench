#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  result_e ;
typedef  int /*<<< orphan*/  mobj_t ;
struct TYPE_5__ {int direction; int speed; int crush; int /*<<< orphan*/  type; TYPE_2__* sector; int /*<<< orphan*/  bottomheight; int /*<<< orphan*/  topheight; } ;
typedef  TYPE_1__ ceiling_t ;
struct TYPE_6__ {int /*<<< orphan*/  soundorg; } ;

/* Variables and functions */
 int CEILSPEED ; 
 int /*<<< orphan*/  P_RemoveActiveCeiling (TYPE_1__*) ; 
 int /*<<< orphan*/  S_StartSound (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_MovePlane (TYPE_2__*,int,int /*<<< orphan*/ ,int,int,int) ; 
#define  crushAndRaise 133 
 int /*<<< orphan*/  crushed ; 
#define  fastCrushAndRaise 132 
 int leveltime ; 
#define  lowerAndCrush 131 
#define  lowerToFloor 130 
 int /*<<< orphan*/  pastdest ; 
#define  raiseToHighest 129 
 int /*<<< orphan*/  sfx_pstop ; 
 int /*<<< orphan*/  sfx_stnmov ; 
#define  silentCrushAndRaise 128 

void T_MoveCeiling (ceiling_t* ceiling)
{
    result_e	res;
	
    switch(ceiling->direction)
    {
      case 0:
	// IN STASIS
	break;
      case 1:
	// UP
	res = T_MovePlane(ceiling->sector,
			  ceiling->speed,
			  ceiling->topheight,
			  false,1,ceiling->direction);
	
	if (!(leveltime&7))
	{
	    switch(ceiling->type)
	    {
	      case silentCrushAndRaise:
		break;
	      default:
		S_StartSound((mobj_t *)&ceiling->sector->soundorg,
			     sfx_stnmov);
		// ?
		break;
	    }
	}
	
	if (res == pastdest)
	{
	    switch(ceiling->type)
	    {
	      case raiseToHighest:
		P_RemoveActiveCeiling(ceiling);
		break;
		
	      case silentCrushAndRaise:
		S_StartSound((mobj_t *)&ceiling->sector->soundorg,
			     sfx_pstop);
	      case fastCrushAndRaise:
	      case crushAndRaise:
		ceiling->direction = -1;
		break;
		
	      default:
		break;
	    }
	    
	}
	break;
	
      case -1:
	// DOWN
	res = T_MovePlane(ceiling->sector,
			  ceiling->speed,
			  ceiling->bottomheight,
			  ceiling->crush,1,ceiling->direction);
	
	if (!(leveltime&7))
	{
	    switch(ceiling->type)
	    {
	      case silentCrushAndRaise: break;
	      default:
		S_StartSound((mobj_t *)&ceiling->sector->soundorg,
			     sfx_stnmov);
	    }
	}
	
	if (res == pastdest)
	{
	    switch(ceiling->type)
	    {
	      case silentCrushAndRaise:
		S_StartSound((mobj_t *)&ceiling->sector->soundorg,
			     sfx_pstop);
	      case crushAndRaise:
		ceiling->speed = CEILSPEED;
	      case fastCrushAndRaise:
		ceiling->direction = 1;
		break;

	      case lowerAndCrush:
	      case lowerToFloor:
		P_RemoveActiveCeiling(ceiling);
		break;

	      default:
		break;
	    }
	}
	else // ( res != pastdest )
	{
	    if (res == crushed)
	    {
		switch(ceiling->type)
		{
		  case silentCrushAndRaise:
		  case crushAndRaise:
		  case lowerAndCrush:
		    ceiling->speed = CEILSPEED / 8;
		    break;

		  default:
		    break;
		}
	    }
	}
	break;
    }
}