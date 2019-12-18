#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int direction; int topcountdown; int type; int topwait; int /*<<< orphan*/  thinker; TYPE_3__* sector; int /*<<< orphan*/  topheight; int /*<<< orphan*/  speed; } ;
typedef  TYPE_1__ vldoor_t ;
typedef  int /*<<< orphan*/  result_e ;
typedef  int /*<<< orphan*/  mobj_t ;
struct TYPE_5__ {int /*<<< orphan*/ * specialdata; int /*<<< orphan*/  soundorg; int /*<<< orphan*/  floorheight; } ;

/* Variables and functions */
 int /*<<< orphan*/  P_RemoveThinker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_StartSound (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_MovePlane (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
#define  blazeClose 135 
#define  blazeOpen 134 
#define  blazeRaise 133 
#define  close 132 
#define  close30ThenOpen 131 
 int /*<<< orphan*/  crushed ; 
#define  normal 130 
#define  open 129 
 int /*<<< orphan*/  pastdest ; 
#define  raiseIn5Mins 128 
 int /*<<< orphan*/  sfx_bdcls ; 
 int /*<<< orphan*/  sfx_dorcls ; 
 int /*<<< orphan*/  sfx_doropn ; 

void T_VerticalDoor (vldoor_t* door)
{
    result_e	res;
	
    switch(door->direction)
    {
      case 0:
	// WAITING
	if (!--door->topcountdown)
	{
	    switch(door->type)
	    {
	      case blazeRaise:
		door->direction = -1; // time to go back down
		S_StartSound((mobj_t *)&door->sector->soundorg,
			     sfx_bdcls);
		break;
		
	      case normal:
		door->direction = -1; // time to go back down
		S_StartSound((mobj_t *)&door->sector->soundorg,
			     sfx_dorcls);
		break;
		
	      case close30ThenOpen:
		door->direction = 1;
		S_StartSound((mobj_t *)&door->sector->soundorg,
			     sfx_doropn);
		break;
		
	      default:
		break;
	    }
	}
	break;
	
      case 2:
	//  INITIAL WAIT
	if (!--door->topcountdown)
	{
	    switch(door->type)
	    {
	      case raiseIn5Mins:
		door->direction = 1;
		door->type = normal;
		S_StartSound((mobj_t *)&door->sector->soundorg,
			     sfx_doropn);
		break;
		
	      default:
		break;
	    }
	}
	break;
	
      case -1:
	// DOWN
	res = T_MovePlane(door->sector,
			  door->speed,
			  door->sector->floorheight,
			  false,1,door->direction);
	if (res == pastdest)
	{
	    switch(door->type)
	    {
	      case blazeRaise:
	      case blazeClose:
		door->sector->specialdata = NULL;
		P_RemoveThinker (&door->thinker);  // unlink and free
		S_StartSound((mobj_t *)&door->sector->soundorg,
			     sfx_bdcls);
		break;
		
	      case normal:
	      case close:
		door->sector->specialdata = NULL;
		P_RemoveThinker (&door->thinker);  // unlink and free
		break;
		
	      case close30ThenOpen:
		door->direction = 0;
		door->topcountdown = 35*30;
		break;
		
	      default:
		break;
	    }
	}
	else if (res == crushed)
	{
	    switch(door->type)
	    {
	      case blazeClose:
	      case close:		// DO NOT GO BACK UP!
		break;
		
	      default:
		door->direction = 1;
		S_StartSound((mobj_t *)&door->sector->soundorg,
			     sfx_doropn);
		break;
	    }
	}
	break;
	
      case 1:
	// UP
	res = T_MovePlane(door->sector,
			  door->speed,
			  door->topheight,
			  false,1,door->direction);
	
	if (res == pastdest)
	{
	    switch(door->type)
	    {
	      case blazeRaise:
	      case normal:
		door->direction = 0; // wait at top
		door->topcountdown = door->topwait;
		break;
		
	      case close30ThenOpen:
	      case blazeOpen:
	      case open:
		door->sector->specialdata = NULL;
		P_RemoveThinker (&door->thinker);  // unlink and free
		break;
		
	      default:
		break;
	    }
	}
	break;
    }
}