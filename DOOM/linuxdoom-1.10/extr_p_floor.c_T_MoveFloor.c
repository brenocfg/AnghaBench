#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ result_e ;
typedef  int /*<<< orphan*/  mobj_t ;
struct TYPE_4__ {int direction; int type; TYPE_2__* sector; int /*<<< orphan*/  thinker; int /*<<< orphan*/  texture; int /*<<< orphan*/  newspecial; int /*<<< orphan*/  crush; int /*<<< orphan*/  floordestheight; int /*<<< orphan*/  speed; } ;
typedef  TYPE_1__ floormove_t ;
struct TYPE_5__ {int /*<<< orphan*/  soundorg; int /*<<< orphan*/  floorpic; int /*<<< orphan*/  special; int /*<<< orphan*/ * specialdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  P_RemoveThinker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_StartSound (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ T_MovePlane (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  donutRaise 129 
 int leveltime ; 
#define  lowerAndChange 128 
 scalar_t__ pastdest ; 
 int /*<<< orphan*/  sfx_pstop ; 
 int /*<<< orphan*/  sfx_stnmov ; 

void T_MoveFloor(floormove_t* floor)
{
    result_e	res;
	
    res = T_MovePlane(floor->sector,
		      floor->speed,
		      floor->floordestheight,
		      floor->crush,0,floor->direction);
    
    if (!(leveltime&7))
	S_StartSound((mobj_t *)&floor->sector->soundorg,
		     sfx_stnmov);
    
    if (res == pastdest)
    {
	floor->sector->specialdata = NULL;

	if (floor->direction == 1)
	{
	    switch(floor->type)
	    {
	      case donutRaise:
		floor->sector->special = floor->newspecial;
		floor->sector->floorpic = floor->texture;
	      default:
		break;
	    }
	}
	else if (floor->direction == -1)
	{
	    switch(floor->type)
	    {
	      case lowerAndChange:
		floor->sector->special = floor->newspecial;
		floor->sector->floorpic = floor->texture;
	      default:
		break;
	    }
	}
	P_RemoveThinker(&floor->thinker);

	S_StartSound((mobj_t *)&floor->sector->soundorg,
		     sfx_pstop);
    }

}