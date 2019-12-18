#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int stair_e ;
struct TYPE_10__ {int floorheight; int floorpic; int linecount; TYPE_4__* specialdata; TYPE_1__** lines; } ;
typedef  TYPE_3__ sector_t ;
typedef  int /*<<< orphan*/  line_t ;
struct TYPE_9__ {void* acp1; } ;
struct TYPE_12__ {TYPE_2__ function; } ;
struct TYPE_11__ {int direction; int speed; int floordestheight; TYPE_3__* sector; TYPE_7__ thinker; } ;
typedef  TYPE_4__ floormove_t ;
typedef  int fixed_t ;
typedef  void* actionf_p1 ;
struct TYPE_8__ {int flags; TYPE_3__* backsector; TYPE_3__* frontsector; } ;

/* Variables and functions */
 int FLOORSPEED ; 
 int FRACUNIT ; 
 int ML_TWOSIDED ; 
 int /*<<< orphan*/  PU_LEVSPEC ; 
 int /*<<< orphan*/  P_AddThinker (TYPE_7__*) ; 
 int P_FindSectorFromLineTag (int /*<<< orphan*/ *,int) ; 
 scalar_t__ T_MoveFloor ; 
 TYPE_4__* Z_Malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  build8 129 
 TYPE_3__* sectors ; 
#define  turbo16 128 

int
EV_BuildStairs
( line_t*	line,
  stair_e	type )
{
    int			secnum;
    int			height;
    int			i;
    int			newsecnum;
    int			texture;
    int			ok;
    int			rtn;
    
    sector_t*		sec;
    sector_t*		tsec;

    floormove_t*	floor;
    
    fixed_t		stairsize;
    fixed_t		speed;

    secnum = -1;
    rtn = 0;
    while ((secnum = P_FindSectorFromLineTag(line,secnum)) >= 0)
    {
	sec = &sectors[secnum];
		
	// ALREADY MOVING?  IF SO, KEEP GOING...
	if (sec->specialdata)
	    continue;
	
	// new floor thinker
	rtn = 1;
	floor = Z_Malloc (sizeof(*floor), PU_LEVSPEC, 0);
	P_AddThinker (&floor->thinker);
	sec->specialdata = floor;
	floor->thinker.function.acp1 = (actionf_p1) T_MoveFloor;
	floor->direction = 1;
	floor->sector = sec;
	switch(type)
	{
	  case build8:
	    speed = FLOORSPEED/4;
	    stairsize = 8*FRACUNIT;
	    break;
	  case turbo16:
	    speed = FLOORSPEED*4;
	    stairsize = 16*FRACUNIT;
	    break;
	}
	floor->speed = speed;
	height = sec->floorheight + stairsize;
	floor->floordestheight = height;
		
	texture = sec->floorpic;
	
	// Find next sector to raise
	// 1.	Find 2-sided line with same sector side[0]
	// 2.	Other side is the next sector to raise
	do
	{
	    ok = 0;
	    for (i = 0;i < sec->linecount;i++)
	    {
		if ( !((sec->lines[i])->flags & ML_TWOSIDED) )
		    continue;
					
		tsec = (sec->lines[i])->frontsector;
		newsecnum = tsec-sectors;
		
		if (secnum != newsecnum)
		    continue;

		tsec = (sec->lines[i])->backsector;
		newsecnum = tsec - sectors;

		if (tsec->floorpic != texture)
		    continue;
					
		height += stairsize;

		if (tsec->specialdata)
		    continue;
					
		sec = tsec;
		secnum = newsecnum;
		floor = Z_Malloc (sizeof(*floor), PU_LEVSPEC, 0);

		P_AddThinker (&floor->thinker);

		sec->specialdata = floor;
		floor->thinker.function.acp1 = (actionf_p1) T_MoveFloor;
		floor->direction = 1;
		floor->sector = sec;
		floor->speed = speed;
		floor->floordestheight = height;
		ok = 1;
		break;
	    }
	} while(ok);
    }
    return rtn;
}