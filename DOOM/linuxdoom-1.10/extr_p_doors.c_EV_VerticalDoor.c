#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ acp1; } ;
struct TYPE_15__ {TYPE_1__ function; } ;
struct TYPE_17__ {int direction; int speed; int topheight; int /*<<< orphan*/  type; int /*<<< orphan*/  topwait; TYPE_3__* sector; TYPE_12__ thinker; } ;
typedef  TYPE_2__ vldoor_t ;
struct TYPE_18__ {TYPE_2__* specialdata; int /*<<< orphan*/  soundorg; } ;
typedef  TYPE_3__ sector_t ;
struct TYPE_19__ {int /*<<< orphan*/  message; int /*<<< orphan*/ * cards; } ;
typedef  TYPE_4__ player_t ;
struct TYPE_20__ {TYPE_4__* player; } ;
typedef  TYPE_5__ mobj_t ;
struct TYPE_21__ {int special; size_t* sidenum; } ;
typedef  TYPE_6__ line_t ;
typedef  scalar_t__ actionf_p1 ;
struct TYPE_22__ {TYPE_3__* sector; } ;

/* Variables and functions */
 int FRACUNIT ; 
 int /*<<< orphan*/  PD_BLUEK ; 
 int /*<<< orphan*/  PD_REDK ; 
 int /*<<< orphan*/  PD_YELLOWK ; 
 int /*<<< orphan*/  PU_LEVSPEC ; 
 int /*<<< orphan*/  P_AddThinker (TYPE_12__*) ; 
 int P_FindLowestCeilingSurrounding (TYPE_3__*) ; 
 int /*<<< orphan*/  S_StartSound (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ T_VerticalDoor ; 
 int VDOORSPEED ; 
 int /*<<< orphan*/  VDOORWAIT ; 
 TYPE_2__* Z_Malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blazeOpen ; 
 int /*<<< orphan*/  blazeRaise ; 
 size_t it_bluecard ; 
 size_t it_blueskull ; 
 size_t it_redcard ; 
 size_t it_redskull ; 
 size_t it_yellowcard ; 
 size_t it_yellowskull ; 
 int /*<<< orphan*/  normal ; 
 int /*<<< orphan*/  open ; 
 TYPE_3__* sectors ; 
 int /*<<< orphan*/  sfx_bdopn ; 
 int /*<<< orphan*/  sfx_doropn ; 
 int /*<<< orphan*/  sfx_oof ; 
 TYPE_7__* sides ; 

void
EV_VerticalDoor
( line_t*	line,
  mobj_t*	thing )
{
    player_t*	player;
    int		secnum;
    sector_t*	sec;
    vldoor_t*	door;
    int		side;
	
    side = 0;	// only front sides can be used

    //	Check for locks
    player = thing->player;
		
    switch(line->special)
    {
      case 26: // Blue Lock
      case 32:
	if ( !player )
	    return;
	
	if (!player->cards[it_bluecard] && !player->cards[it_blueskull])
	{
	    player->message = PD_BLUEK;
	    S_StartSound(NULL,sfx_oof);
	    return;
	}
	break;
	
      case 27: // Yellow Lock
      case 34:
	if ( !player )
	    return;
	
	if (!player->cards[it_yellowcard] &&
	    !player->cards[it_yellowskull])
	{
	    player->message = PD_YELLOWK;
	    S_StartSound(NULL,sfx_oof);
	    return;
	}
	break;
	
      case 28: // Red Lock
      case 33:
	if ( !player )
	    return;
	
	if (!player->cards[it_redcard] && !player->cards[it_redskull])
	{
	    player->message = PD_REDK;
	    S_StartSound(NULL,sfx_oof);
	    return;
	}
	break;
    }
	
    // if the sector has an active thinker, use it
    sec = sides[ line->sidenum[side^1]] .sector;
    secnum = sec-sectors;

    if (sec->specialdata)
    {
	door = sec->specialdata;
	switch(line->special)
	{
	  case	1: // ONLY FOR "RAISE" DOORS, NOT "OPEN"s
	  case	26:
	  case	27:
	  case	28:
	  case	117:
	    if (door->direction == -1)
		door->direction = 1;	// go back up
	    else
	    {
		if (!thing->player)
		    return;		// JDC: bad guys never close doors
		
		door->direction = -1;	// start going down immediately
	    }
	    return;
	}
    }
	
    // for proper sound
    switch(line->special)
    {
      case 117:	// BLAZING DOOR RAISE
      case 118:	// BLAZING DOOR OPEN
	S_StartSound((mobj_t *)&sec->soundorg,sfx_bdopn);
	break;
	
      case 1:	// NORMAL DOOR SOUND
      case 31:
	S_StartSound((mobj_t *)&sec->soundorg,sfx_doropn);
	break;
	
      default:	// LOCKED DOOR SOUND
	S_StartSound((mobj_t *)&sec->soundorg,sfx_doropn);
	break;
    }
	
    
    // new door thinker
    door = Z_Malloc (sizeof(*door), PU_LEVSPEC, 0);
    P_AddThinker (&door->thinker);
    sec->specialdata = door;
    door->thinker.function.acp1 = (actionf_p1) T_VerticalDoor;
    door->sector = sec;
    door->direction = 1;
    door->speed = VDOORSPEED;
    door->topwait = VDOORWAIT;

    switch(line->special)
    {
      case 1:
      case 26:
      case 27:
      case 28:
	door->type = normal;
	break;
	
      case 31:
      case 32:
      case 33:
      case 34:
	door->type = open;
	line->special = 0;
	break;
	
      case 117:	// blazing door raise
	door->type = blazeRaise;
	door->speed = VDOORSPEED*4;
	break;
      case 118:	// blazing door open
	door->type = blazeOpen;
	line->special = 0;
	door->speed = VDOORSPEED*4;
	break;
    }
    
    // find the top and bottom of the movement range
    door->topheight = P_FindLowestCeilingSurrounding(sec);
    door->topheight -= 4*FRACUNIT;
}