#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; scalar_t__ radius; int /*<<< orphan*/  player; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_1__ mobj_t ;
typedef  scalar_t__ fixed_t ;
typedef  int boolean ;

/* Variables and functions */
 int MF_SHOOTABLE ; 
 int /*<<< orphan*/  P_DamageMobj (TYPE_1__*,TYPE_1__*,TYPE_1__*,int) ; 
 scalar_t__ abs (scalar_t__) ; 
 int gamemap ; 
 TYPE_1__* tmthing ; 
 scalar_t__ tmx ; 
 scalar_t__ tmy ; 

boolean PIT_StompThing (mobj_t* thing)
{
    fixed_t	blockdist;
		
    if (!(thing->flags & MF_SHOOTABLE) )
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
    
    // monsters don't stomp things except on boss level
    if ( !tmthing->player && gamemap != 30)
	return false;	
		
    P_DamageMobj (thing, tmthing, tmthing, 10000);
	
    return true;
}