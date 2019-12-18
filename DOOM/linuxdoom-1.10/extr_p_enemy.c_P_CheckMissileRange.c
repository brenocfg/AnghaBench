#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; scalar_t__ type; TYPE_1__* info; TYPE_4__* target; scalar_t__ y; scalar_t__ x; scalar_t__ reactiontime; } ;
typedef  TYPE_2__ mobj_t ;
typedef  int fixed_t ;
typedef  int boolean ;
struct TYPE_8__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_6__ {int /*<<< orphan*/  meleestate; } ;

/* Variables and functions */
 int FRACUNIT ; 
 int MF_JUSTHIT ; 
 scalar_t__ MT_CYBORG ; 
 scalar_t__ MT_SKULL ; 
 scalar_t__ MT_SPIDER ; 
 scalar_t__ MT_UNDEAD ; 
 scalar_t__ MT_VILE ; 
 int P_AproxDistance (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  P_CheckSight (TYPE_2__*,TYPE_4__*) ; 
 int P_Random () ; 

boolean P_CheckMissileRange (mobj_t* actor)
{
    fixed_t	dist;
	
    if (! P_CheckSight (actor, actor->target) )
	return false;
	
    if ( actor->flags & MF_JUSTHIT )
    {
	// the target just hit the enemy,
	// so fight back!
	actor->flags &= ~MF_JUSTHIT;
	return true;
    }
	
    if (actor->reactiontime)
	return false;	// do not attack yet
		
    // OPTIMIZE: get this from a global checksight
    dist = P_AproxDistance ( actor->x-actor->target->x,
			     actor->y-actor->target->y) - 64*FRACUNIT;
    
    if (!actor->info->meleestate)
	dist -= 128*FRACUNIT;	// no melee attack, so fire more

    dist >>= 16;

    if (actor->type == MT_VILE)
    {
	if (dist > 14*64)	
	    return false;	// too far away
    }
	

    if (actor->type == MT_UNDEAD)
    {
	if (dist < 196)	
	    return false;	// close for fist attack
	dist >>= 1;
    }
	

    if (actor->type == MT_CYBORG
	|| actor->type == MT_SPIDER
	|| actor->type == MT_SKULL)
    {
	dist >>= 1;
    }
    
    if (dist > 200)
	dist = 200;
		
    if (actor->type == MT_CYBORG && dist > 160)
	dist = 160;
		
    if (P_Random () < dist)
	return false;
		
    return true;
}