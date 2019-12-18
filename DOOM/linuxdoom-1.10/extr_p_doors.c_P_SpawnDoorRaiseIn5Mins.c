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
struct TYPE_9__ {int direction; int topheight; int topcountdown; int /*<<< orphan*/  topwait; int /*<<< orphan*/  speed; int /*<<< orphan*/  type; TYPE_3__* sector; TYPE_7__ thinker; } ;
typedef  TYPE_2__ vldoor_t ;
struct TYPE_10__ {scalar_t__ special; TYPE_2__* specialdata; } ;
typedef  TYPE_3__ sector_t ;
typedef  scalar_t__ actionf_p1 ;

/* Variables and functions */
 int FRACUNIT ; 
 int /*<<< orphan*/  PU_LEVSPEC ; 
 int /*<<< orphan*/  P_AddThinker (TYPE_7__*) ; 
 int P_FindLowestCeilingSurrounding (TYPE_3__*) ; 
 scalar_t__ T_VerticalDoor ; 
 int /*<<< orphan*/  VDOORSPEED ; 
 int /*<<< orphan*/  VDOORWAIT ; 
 TYPE_2__* Z_Malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raiseIn5Mins ; 

void
P_SpawnDoorRaiseIn5Mins
( sector_t*	sec,
  int		secnum )
{
    vldoor_t*	door;
	
    door = Z_Malloc ( sizeof(*door), PU_LEVSPEC, 0);
    
    P_AddThinker (&door->thinker);

    sec->specialdata = door;
    sec->special = 0;

    door->thinker.function.acp1 = (actionf_p1)T_VerticalDoor;
    door->sector = sec;
    door->direction = 2;
    door->type = raiseIn5Mins;
    door->speed = VDOORSPEED;
    door->topheight = P_FindLowestCeilingSurrounding(sec);
    door->topheight -= 4*FRACUNIT;
    door->topwait = VDOORWAIT;
    door->topcountdown = 5 * 60 * 35;
}