#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int linecount; int /*<<< orphan*/  floorheight; TYPE_3__* specialdata; int /*<<< orphan*/  floorpic; TYPE_6__** lines; } ;
typedef  TYPE_2__ sector_t ;
typedef  int /*<<< orphan*/  line_t ;
struct TYPE_10__ {void* acp1; } ;
struct TYPE_14__ {TYPE_1__ function; } ;
struct TYPE_12__ {int crush; int direction; int speed; int /*<<< orphan*/  floordestheight; TYPE_2__* sector; int /*<<< orphan*/  type; TYPE_9__ thinker; scalar_t__ newspecial; int /*<<< orphan*/  texture; } ;
typedef  TYPE_3__ floormove_t ;
typedef  void* actionf_p1 ;
struct TYPE_13__ {TYPE_2__* backsector; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int FLOORSPEED ; 
 int ML_TWOSIDED ; 
 int /*<<< orphan*/  PU_LEVSPEC ; 
 int /*<<< orphan*/  P_AddThinker (TYPE_9__*) ; 
 int P_FindSectorFromLineTag (int /*<<< orphan*/ *,int) ; 
 scalar_t__ T_MoveFloor ; 
 TYPE_3__* Z_Malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  donutRaise ; 
 TYPE_2__* getNextSector (TYPE_6__*,TYPE_2__*) ; 
 int /*<<< orphan*/  lowerFloor ; 
 TYPE_2__* sectors ; 

int EV_DoDonut(line_t*	line)
{
    sector_t*		s1;
    sector_t*		s2;
    sector_t*		s3;
    int			secnum;
    int			rtn;
    int			i;
    floormove_t*	floor;
	
    secnum = -1;
    rtn = 0;
    while ((secnum = P_FindSectorFromLineTag(line,secnum)) >= 0)
    {
	s1 = &sectors[secnum];
		
	// ALREADY MOVING?  IF SO, KEEP GOING...
	if (s1->specialdata)
	    continue;
			
	rtn = 1;
	s2 = getNextSector(s1->lines[0],s1);
	for (i = 0;i < s2->linecount;i++)
	{
	    if ((!s2->lines[i]->flags & ML_TWOSIDED) ||
		(s2->lines[i]->backsector == s1))
		continue;
	    s3 = s2->lines[i]->backsector;
	    
	    //	Spawn rising slime
	    floor = Z_Malloc (sizeof(*floor), PU_LEVSPEC, 0);
	    P_AddThinker (&floor->thinker);
	    s2->specialdata = floor;
	    floor->thinker.function.acp1 = (actionf_p1) T_MoveFloor;
	    floor->type = donutRaise;
	    floor->crush = false;
	    floor->direction = 1;
	    floor->sector = s2;
	    floor->speed = FLOORSPEED / 2;
	    floor->texture = s3->floorpic;
	    floor->newspecial = 0;
	    floor->floordestheight = s3->floorheight;
	    
	    //	Spawn lowering donut-hole
	    floor = Z_Malloc (sizeof(*floor), PU_LEVSPEC, 0);
	    P_AddThinker (&floor->thinker);
	    s1->specialdata = floor;
	    floor->thinker.function.acp1 = (actionf_p1) T_MoveFloor;
	    floor->type = lowerFloor;
	    floor->crush = false;
	    floor->direction = -1;
	    floor->sector = s1;
	    floor->speed = FLOORSPEED / 2;
	    floor->floordestheight = s3->floorheight;
	    break;
	}
    }
    return rtn;
}