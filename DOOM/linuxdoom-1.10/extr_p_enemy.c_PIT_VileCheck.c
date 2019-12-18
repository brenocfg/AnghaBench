#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; int tics; int height; scalar_t__ y; scalar_t__ x; scalar_t__ momy; scalar_t__ momx; TYPE_1__* info; } ;
typedef  TYPE_2__ mobj_t ;
typedef  int boolean ;
struct TYPE_9__ {int radius; } ;
struct TYPE_7__ {scalar_t__ raisestate; int radius; } ;

/* Variables and functions */
 int MF_CORPSE ; 
 size_t MT_VILE ; 
 int P_CheckPosition (TYPE_2__*,scalar_t__,scalar_t__) ; 
 scalar_t__ S_NULL ; 
 int abs (scalar_t__) ; 
 TYPE_2__* corpsehit ; 
 TYPE_3__* mobjinfo ; 
 scalar_t__ viletryx ; 
 scalar_t__ viletryy ; 

boolean PIT_VileCheck (mobj_t*	thing)
{
    int		maxdist;
    boolean	check;
	
    if (!(thing->flags & MF_CORPSE) )
	return true;	// not a monster
    
    if (thing->tics != -1)
	return true;	// not lying still yet
    
    if (thing->info->raisestate == S_NULL)
	return true;	// monster doesn't have a raise state
    
    maxdist = thing->info->radius + mobjinfo[MT_VILE].radius;
	
    if ( abs(thing->x - viletryx) > maxdist
	 || abs(thing->y - viletryy) > maxdist )
	return true;		// not actually touching
		
    corpsehit = thing;
    corpsehit->momx = corpsehit->momy = 0;
    corpsehit->height <<= 2;
    check = P_CheckPosition (corpsehit, corpsehit->x, corpsehit->y);
    corpsehit->height >>= 2;

    if (!check)
	return true;		// doesn't fit here
		
    return false;		// got one, so stop checking
}