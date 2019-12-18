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
struct TYPE_12__ {int flags; scalar_t__ radius; scalar_t__ z; scalar_t__ height; scalar_t__ type; struct TYPE_12__* target; TYPE_1__* info; scalar_t__ momz; scalar_t__ momy; scalar_t__ momx; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_2__ mobj_t ;
typedef  scalar_t__ fixed_t ;
typedef  int boolean ;
struct TYPE_11__ {int damage; int /*<<< orphan*/  spawnstate; } ;

/* Variables and functions */
 int MF_MISSILE ; 
 int MF_PICKUP ; 
 int MF_SHOOTABLE ; 
 int MF_SKULLFLY ; 
 int MF_SOLID ; 
 int MF_SPECIAL ; 
 scalar_t__ MT_BRUISER ; 
 scalar_t__ MT_KNIGHT ; 
 scalar_t__ MT_PLAYER ; 
 int /*<<< orphan*/  P_DamageMobj (TYPE_2__*,TYPE_2__*,TYPE_2__*,int) ; 
 int P_Random () ; 
 int /*<<< orphan*/  P_SetMobjState (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_TouchSpecialThing (TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ abs (scalar_t__) ; 
 int tmflags ; 
 TYPE_2__* tmthing ; 
 scalar_t__ tmx ; 
 scalar_t__ tmy ; 

boolean PIT_CheckThing (mobj_t* thing)
{
    fixed_t		blockdist;
    boolean		solid;
    int			damage;
		
    if (!(thing->flags & (MF_SOLID|MF_SPECIAL|MF_SHOOTABLE) ))
	return true;
    
    blockdist = thing->radius + tmthing->radius;

    if ( abs(thing->x - tmx) >= blockdist
	 || abs(thing->y - tmy) >= blockdist )
    {
	// didn't hit it
	return true;	
    }
    
    // don't clip against self
    if (thing == tmthing)
	return true;
    
    // check for skulls slamming into things
    if (tmthing->flags & MF_SKULLFLY)
    {
	damage = ((P_Random()%8)+1)*tmthing->info->damage;
	
	P_DamageMobj (thing, tmthing, tmthing, damage);
	
	tmthing->flags &= ~MF_SKULLFLY;
	tmthing->momx = tmthing->momy = tmthing->momz = 0;
	
	P_SetMobjState (tmthing, tmthing->info->spawnstate);
	
	return false;		// stop moving
    }

    
    // missiles can hit other things
    if (tmthing->flags & MF_MISSILE)
    {
	// see if it went over / under
	if (tmthing->z > thing->z + thing->height)
	    return true;		// overhead
	if (tmthing->z+tmthing->height < thing->z)
	    return true;		// underneath
		
	if (tmthing->target && (
	    tmthing->target->type == thing->type || 
	    (tmthing->target->type == MT_KNIGHT && thing->type == MT_BRUISER)||
	    (tmthing->target->type == MT_BRUISER && thing->type == MT_KNIGHT) ) )
	{
	    // Don't hit same species as originator.
	    if (thing == tmthing->target)
		return true;

	    if (thing->type != MT_PLAYER)
	    {
		// Explode, but do no damage.
		// Let players missile other players.
		return false;
	    }
	}
	
	if (! (thing->flags & MF_SHOOTABLE) )
	{
	    // didn't do any damage
	    return !(thing->flags & MF_SOLID);	
	}
	
	// damage / explode
	damage = ((P_Random()%8)+1)*tmthing->info->damage;
	P_DamageMobj (thing, tmthing, tmthing->target, damage);

	// don't traverse any more
	return false;				
    }
    
    // check for special pickup
    if (thing->flags & MF_SPECIAL)
    {
	solid = thing->flags&MF_SOLID;
	if (tmflags&MF_PICKUP)
	{
	    // can remove thing
	    P_TouchSpecialThing (thing, tmthing);
	}
	return !solid;
    }
	
    return !(thing->flags & MF_SOLID);
}