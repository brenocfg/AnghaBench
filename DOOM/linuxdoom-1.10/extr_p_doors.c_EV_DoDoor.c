#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ acp1; } ;
struct TYPE_11__ {TYPE_1__ function; } ;
struct TYPE_9__ {int type; int speed; int topheight; int direction; TYPE_3__* sector; int /*<<< orphan*/  topwait; TYPE_7__ thinker; } ;
typedef  TYPE_2__ vldoor_t ;
typedef  int vldoor_e ;
struct TYPE_10__ {int ceilingheight; int /*<<< orphan*/  soundorg; TYPE_2__* specialdata; } ;
typedef  TYPE_3__ sector_t ;
typedef  int /*<<< orphan*/  mobj_t ;
typedef  int /*<<< orphan*/  line_t ;
typedef  scalar_t__ actionf_p1 ;

/* Variables and functions */
 int FRACUNIT ; 
 int /*<<< orphan*/  PU_LEVSPEC ; 
 int /*<<< orphan*/  P_AddThinker (TYPE_7__*) ; 
 void* P_FindLowestCeilingSurrounding (TYPE_3__*) ; 
 int P_FindSectorFromLineTag (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  S_StartSound (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ T_VerticalDoor ; 
 int VDOORSPEED ; 
 int /*<<< orphan*/  VDOORWAIT ; 
 TYPE_2__* Z_Malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  blazeClose 134 
#define  blazeOpen 133 
#define  blazeRaise 132 
#define  close 131 
#define  close30ThenOpen 130 
#define  normal 129 
#define  open 128 
 TYPE_3__* sectors ; 
 int /*<<< orphan*/  sfx_bdcls ; 
 int /*<<< orphan*/  sfx_bdopn ; 
 int /*<<< orphan*/  sfx_dorcls ; 
 int /*<<< orphan*/  sfx_doropn ; 

int
EV_DoDoor
( line_t*	line,
  vldoor_e	type )
{
    int		secnum,rtn;
    sector_t*	sec;
    vldoor_t*	door;
	
    secnum = -1;
    rtn = 0;
    
    while ((secnum = P_FindSectorFromLineTag(line,secnum)) >= 0)
    {
	sec = &sectors[secnum];
	if (sec->specialdata)
	    continue;
		
	
	// new door thinker
	rtn = 1;
	door = Z_Malloc (sizeof(*door), PU_LEVSPEC, 0);
	P_AddThinker (&door->thinker);
	sec->specialdata = door;

	door->thinker.function.acp1 = (actionf_p1) T_VerticalDoor;
	door->sector = sec;
	door->type = type;
	door->topwait = VDOORWAIT;
	door->speed = VDOORSPEED;
		
	switch(type)
	{
	  case blazeClose:
	    door->topheight = P_FindLowestCeilingSurrounding(sec);
	    door->topheight -= 4*FRACUNIT;
	    door->direction = -1;
	    door->speed = VDOORSPEED * 4;
	    S_StartSound((mobj_t *)&door->sector->soundorg,
			 sfx_bdcls);
	    break;
	    
	  case close:
	    door->topheight = P_FindLowestCeilingSurrounding(sec);
	    door->topheight -= 4*FRACUNIT;
	    door->direction = -1;
	    S_StartSound((mobj_t *)&door->sector->soundorg,
			 sfx_dorcls);
	    break;
	    
	  case close30ThenOpen:
	    door->topheight = sec->ceilingheight;
	    door->direction = -1;
	    S_StartSound((mobj_t *)&door->sector->soundorg,
			 sfx_dorcls);
	    break;
	    
	  case blazeRaise:
	  case blazeOpen:
	    door->direction = 1;
	    door->topheight = P_FindLowestCeilingSurrounding(sec);
	    door->topheight -= 4*FRACUNIT;
	    door->speed = VDOORSPEED * 4;
	    if (door->topheight != sec->ceilingheight)
		S_StartSound((mobj_t *)&door->sector->soundorg,
			     sfx_bdopn);
	    break;
	    
	  case normal:
	  case open:
	    door->direction = 1;
	    door->topheight = P_FindLowestCeilingSurrounding(sec);
	    door->topheight -= 4*FRACUNIT;
	    if (door->topheight != sec->ceilingheight)
		S_StartSound((mobj_t *)&door->sector->soundorg,
			     sfx_doropn);
	    break;
	    
	  default:
	    break;
	}
		
    }
    return rtn;
}