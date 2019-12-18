#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ health; int flags; int height; int momx; int momy; scalar_t__ z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; scalar_t__ radius; } ;
typedef  TYPE_1__ mobj_t ;
typedef  int boolean ;

/* Variables and functions */
 int MF_DROPPED ; 
 int MF_SHOOTABLE ; 
 int MF_SOLID ; 
 int /*<<< orphan*/  MT_BLOOD ; 
 int /*<<< orphan*/  P_DamageMobj (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int P_Random () ; 
 int /*<<< orphan*/  P_RemoveMobj (TYPE_1__*) ; 
 int /*<<< orphan*/  P_SetMobjState (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* P_SpawnMobj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ P_ThingHeightClip (TYPE_1__*) ; 
 int /*<<< orphan*/  S_GIBS ; 
 scalar_t__ crushchange ; 
 int leveltime ; 
 int nofit ; 

boolean PIT_ChangeSector (mobj_t*	thing)
{
    mobj_t*	mo;
	
    if (P_ThingHeightClip (thing))
    {
	// keep checking
	return true;
    }
    

    // crunch bodies to giblets
    if (thing->health <= 0)
    {
	P_SetMobjState (thing, S_GIBS);

	thing->flags &= ~MF_SOLID;
	thing->height = 0;
	thing->radius = 0;

	// keep checking
	return true;		
    }

    // crunch dropped items
    if (thing->flags & MF_DROPPED)
    {
	P_RemoveMobj (thing);
	
	// keep checking
	return true;		
    }

    if (! (thing->flags & MF_SHOOTABLE) )
    {
	// assume it is bloody gibs or something
	return true;			
    }
    
    nofit = true;

    if (crushchange && !(leveltime&3) )
    {
	P_DamageMobj(thing,NULL,NULL,10);

	// spray blood in a random direction
	mo = P_SpawnMobj (thing->x,
			  thing->y,
			  thing->z + thing->height/2, MT_BLOOD);
	
	mo->momx = (P_Random() - P_Random ())<<12;
	mo->momy = (P_Random() - P_Random ())<<12;
    }

    // keep checking (crush other things)	
    return true;	
}