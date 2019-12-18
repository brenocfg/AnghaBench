#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int movedir; int angle; int flags; scalar_t__ movecount; TYPE_1__* info; TYPE_9__* target; scalar_t__ threshold; scalar_t__ reactiontime; } ;
typedef  TYPE_2__ mobj_t ;
struct TYPE_15__ {scalar_t__ health; int flags; } ;
struct TYPE_13__ {scalar_t__ activesound; scalar_t__ missilestate; scalar_t__ meleestate; scalar_t__ attacksound; scalar_t__ spawnstate; } ;

/* Variables and functions */
 int ANG90 ; 
 int MF_JUSTATTACKED ; 
 int MF_SHOOTABLE ; 
 scalar_t__ P_CheckMeleeRange (TYPE_2__*) ; 
 int /*<<< orphan*/  P_CheckMissileRange (TYPE_2__*) ; 
 int /*<<< orphan*/  P_CheckSight (TYPE_2__*,TYPE_9__*) ; 
 scalar_t__ P_LookForPlayers (TYPE_2__*,int) ; 
 int /*<<< orphan*/  P_Move (TYPE_2__*) ; 
 int /*<<< orphan*/  P_NewChaseDir (TYPE_2__*) ; 
 int P_Random () ; 
 int /*<<< orphan*/  P_SetMobjState (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  S_StartSound (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  fastparm ; 
 scalar_t__ gameskill ; 
 scalar_t__ netgame ; 
 scalar_t__ sk_nightmare ; 

void A_Chase (mobj_t*	actor)
{
    int		delta;

    if (actor->reactiontime)
	actor->reactiontime--;
				

    // modify target threshold
    if  (actor->threshold)
    {
	if (!actor->target
	    || actor->target->health <= 0)
	{
	    actor->threshold = 0;
	}
	else
	    actor->threshold--;
    }
    
    // turn towards movement direction if not there yet
    if (actor->movedir < 8)
    {
	actor->angle &= (7<<29);
	delta = actor->angle - (actor->movedir << 29);
	
	if (delta > 0)
	    actor->angle -= ANG90/2;
	else if (delta < 0)
	    actor->angle += ANG90/2;
    }

    if (!actor->target
	|| !(actor->target->flags&MF_SHOOTABLE))
    {
	// look for a new target
	if (P_LookForPlayers(actor,true))
	    return; 	// got a new target
	
	P_SetMobjState (actor, actor->info->spawnstate);
	return;
    }
    
    // do not attack twice in a row
    if (actor->flags & MF_JUSTATTACKED)
    {
	actor->flags &= ~MF_JUSTATTACKED;
	if (gameskill != sk_nightmare && !fastparm)
	    P_NewChaseDir (actor);
	return;
    }
    
    // check for melee attack
    if (actor->info->meleestate
	&& P_CheckMeleeRange (actor))
    {
	if (actor->info->attacksound)
	    S_StartSound (actor, actor->info->attacksound);

	P_SetMobjState (actor, actor->info->meleestate);
	return;
    }
    
    // check for missile attack
    if (actor->info->missilestate)
    {
	if (gameskill < sk_nightmare
	    && !fastparm && actor->movecount)
	{
	    goto nomissile;
	}
	
	if (!P_CheckMissileRange (actor))
	    goto nomissile;
	
	P_SetMobjState (actor, actor->info->missilestate);
	actor->flags |= MF_JUSTATTACKED;
	return;
    }

    // ?
  nomissile:
    // possibly choose another target
    if (netgame
	&& !actor->threshold
	&& !P_CheckSight (actor, actor->target) )
    {
	if (P_LookForPlayers(actor,true))
	    return;	// got a new target
    }
    
    // chase towards player
    if (--actor->movecount<0
	|| !P_Move (actor))
    {
	P_NewChaseDir (actor);
    }
    
    // make active sound
    if (actor->info->activesound
	&& P_Random () < 3)
    {
	S_StartSound (actor, actor->info->activesound);
    }
}