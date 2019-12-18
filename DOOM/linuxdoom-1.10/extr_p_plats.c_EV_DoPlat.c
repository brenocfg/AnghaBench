#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  soundorg; void* floorheight; int /*<<< orphan*/  floorpic; int /*<<< orphan*/  special; TYPE_4__* specialdata; } ;
typedef  TYPE_3__ sector_t ;
typedef  int plattype_e ;
struct TYPE_17__ {scalar_t__ acp1; } ;
struct TYPE_16__ {TYPE_1__ function; } ;
struct TYPE_20__ {int type; int crush; int speed; int wait; int status; void* high; void* low; int /*<<< orphan*/  tag; TYPE_13__ thinker; TYPE_3__* sector; } ;
typedef  TYPE_4__ plat_t ;
typedef  int /*<<< orphan*/  mobj_t ;
struct TYPE_21__ {size_t* sidenum; int /*<<< orphan*/  tag; } ;
typedef  TYPE_5__ line_t ;
typedef  scalar_t__ actionf_p1 ;
struct TYPE_22__ {TYPE_2__* sector; } ;
struct TYPE_18__ {int /*<<< orphan*/  floorpic; } ;

/* Variables and functions */
 int FRACUNIT ; 
 int PLATSPEED ; 
 int PLATWAIT ; 
 int /*<<< orphan*/  PU_LEVSPEC ; 
 int /*<<< orphan*/  P_ActivateInStasis (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_AddActivePlat (TYPE_4__*) ; 
 int /*<<< orphan*/  P_AddThinker (TYPE_13__*) ; 
 void* P_FindHighestFloorSurrounding (TYPE_3__*) ; 
 void* P_FindLowestFloorSurrounding (TYPE_3__*) ; 
 void* P_FindNextHighestFloor (TYPE_3__*,void*) ; 
 int P_FindSectorFromLineTag (TYPE_5__*,int) ; 
 int P_Random () ; 
 int /*<<< orphan*/  S_StartSound (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ T_PlatRaise ; 
 TYPE_4__* Z_Malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  blazeDWUS 132 
 void* down ; 
#define  downWaitUpStay 131 
#define  perpetualRaise 130 
#define  raiseAndChange 129 
#define  raiseToNearestAndChange 128 
 TYPE_3__* sectors ; 
 int /*<<< orphan*/  sfx_pstart ; 
 int /*<<< orphan*/  sfx_stnmov ; 
 TYPE_6__* sides ; 
 void* up ; 

int
EV_DoPlat
( line_t*	line,
  plattype_e	type,
  int		amount )
{
    plat_t*	plat;
    int		secnum;
    int		rtn;
    sector_t*	sec;
	
    secnum = -1;
    rtn = 0;

    
    //	Activate all <type> plats that are in_stasis
    switch(type)
    {
      case perpetualRaise:
	P_ActivateInStasis(line->tag);
	break;
	
      default:
	break;
    }
	
    while ((secnum = P_FindSectorFromLineTag(line,secnum)) >= 0)
    {
	sec = &sectors[secnum];

	if (sec->specialdata)
	    continue;
	
	// Find lowest & highest floors around sector
	rtn = 1;
	plat = Z_Malloc( sizeof(*plat), PU_LEVSPEC, 0);
	P_AddThinker(&plat->thinker);
		
	plat->type = type;
	plat->sector = sec;
	plat->sector->specialdata = plat;
	plat->thinker.function.acp1 = (actionf_p1) T_PlatRaise;
	plat->crush = false;
	plat->tag = line->tag;
	
	switch(type)
	{
	  case raiseToNearestAndChange:
	    plat->speed = PLATSPEED/2;
	    sec->floorpic = sides[line->sidenum[0]].sector->floorpic;
	    plat->high = P_FindNextHighestFloor(sec,sec->floorheight);
	    plat->wait = 0;
	    plat->status = up;
	    // NO MORE DAMAGE, IF APPLICABLE
	    sec->special = 0;		

	    S_StartSound((mobj_t *)&sec->soundorg,sfx_stnmov);
	    break;
	    
	  case raiseAndChange:
	    plat->speed = PLATSPEED/2;
	    sec->floorpic = sides[line->sidenum[0]].sector->floorpic;
	    plat->high = sec->floorheight + amount*FRACUNIT;
	    plat->wait = 0;
	    plat->status = up;

	    S_StartSound((mobj_t *)&sec->soundorg,sfx_stnmov);
	    break;
	    
	  case downWaitUpStay:
	    plat->speed = PLATSPEED * 4;
	    plat->low = P_FindLowestFloorSurrounding(sec);

	    if (plat->low > sec->floorheight)
		plat->low = sec->floorheight;

	    plat->high = sec->floorheight;
	    plat->wait = 35*PLATWAIT;
	    plat->status = down;
	    S_StartSound((mobj_t *)&sec->soundorg,sfx_pstart);
	    break;
	    
	  case blazeDWUS:
	    plat->speed = PLATSPEED * 8;
	    plat->low = P_FindLowestFloorSurrounding(sec);

	    if (plat->low > sec->floorheight)
		plat->low = sec->floorheight;

	    plat->high = sec->floorheight;
	    plat->wait = 35*PLATWAIT;
	    plat->status = down;
	    S_StartSound((mobj_t *)&sec->soundorg,sfx_pstart);
	    break;
	    
	  case perpetualRaise:
	    plat->speed = PLATSPEED;
	    plat->low = P_FindLowestFloorSurrounding(sec);

	    if (plat->low > sec->floorheight)
		plat->low = sec->floorheight;

	    plat->high = P_FindHighestFloorSurrounding(sec);

	    if (plat->high < sec->floorheight)
		plat->high = sec->floorheight;

	    plat->wait = 35*PLATWAIT;
	    plat->status = P_Random()&1;

	    S_StartSound((mobj_t *)&sec->soundorg,sfx_pstart);
	    break;
	}
	P_AddActivePlat(plat);
    }
    return rtn;
}