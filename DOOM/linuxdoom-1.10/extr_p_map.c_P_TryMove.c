#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int flags; scalar_t__ height; scalar_t__ z; void* x; void* y; scalar_t__ ceilingz; scalar_t__ floorz; } ;
typedef  TYPE_1__ mobj_t ;
struct TYPE_12__ {scalar_t__ special; } ;
typedef  TYPE_2__ line_t ;
typedef  void* fixed_t ;
typedef  int boolean ;

/* Variables and functions */
 int FRACUNIT ; 
 int MF_DROPOFF ; 
 int MF_FLOAT ; 
 int MF_NOCLIP ; 
 int MF_TELEPORT ; 
 int /*<<< orphan*/  P_CheckPosition (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  P_CrossSpecialLine (TYPE_2__*,int,TYPE_1__*) ; 
 int P_PointOnLineSide (void*,void*,TYPE_2__*) ; 
 int /*<<< orphan*/  P_SetThingPosition (TYPE_1__*) ; 
 int /*<<< orphan*/  P_UnsetThingPosition (TYPE_1__*) ; 
 int floatok ; 
 int lines ; 
 size_t numspechit ; 
 TYPE_2__** spechit ; 
 scalar_t__ tmceilingz ; 
 scalar_t__ tmdropoffz ; 
 scalar_t__ tmfloorz ; 

boolean
P_TryMove
( mobj_t*	thing,
  fixed_t	x,
  fixed_t	y )
{
    fixed_t	oldx;
    fixed_t	oldy;
    int		side;
    int		oldside;
    line_t*	ld;

    floatok = false;
    if (!P_CheckPosition (thing, x, y))
	return false;		// solid wall or thing
    
    if ( !(thing->flags & MF_NOCLIP) )
    {
	if (tmceilingz - tmfloorz < thing->height)
	    return false;	// doesn't fit

	floatok = true;
	
	if ( !(thing->flags&MF_TELEPORT) 
	     &&tmceilingz - thing->z < thing->height)
	    return false;	// mobj must lower itself to fit

	if ( !(thing->flags&MF_TELEPORT)
	     && tmfloorz - thing->z > 24*FRACUNIT )
	    return false;	// too big a step up

	if ( !(thing->flags&(MF_DROPOFF|MF_FLOAT))
	     && tmfloorz - tmdropoffz > 24*FRACUNIT )
	    return false;	// don't stand over a dropoff
    }
    
    // the move is ok,
    // so link the thing into its new position
    P_UnsetThingPosition (thing);

    oldx = thing->x;
    oldy = thing->y;
    thing->floorz = tmfloorz;
    thing->ceilingz = tmceilingz;	
    thing->x = x;
    thing->y = y;

    P_SetThingPosition (thing);
    
    // if any special lines were hit, do the effect
    if (! (thing->flags&(MF_TELEPORT|MF_NOCLIP)) )
    {
	while (numspechit--)
	{
	    // see if the line was crossed
	    ld = spechit[numspechit];
	    side = P_PointOnLineSide (thing->x, thing->y, ld);
	    oldside = P_PointOnLineSide (oldx, oldy, ld);
	    if (side != oldside)
	    {
		if (ld->special)
		    P_CrossSpecialLine (ld-lines, oldside, thing);
	    }
	}
    }

    return true;
}