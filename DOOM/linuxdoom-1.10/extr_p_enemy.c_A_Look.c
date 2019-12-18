#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int flags; scalar_t__ type; TYPE_3__* info; struct TYPE_14__* target; TYPE_2__* subsector; scalar_t__ threshold; } ;
typedef  TYPE_4__ mobj_t ;
struct TYPE_13__ {int seesound; int /*<<< orphan*/  seestate; } ;
struct TYPE_12__ {TYPE_1__* sector; } ;
struct TYPE_11__ {TYPE_4__* soundtarget; } ;

/* Variables and functions */
 int MF_AMBUSH ; 
 int MF_SHOOTABLE ; 
 scalar_t__ MT_CYBORG ; 
 scalar_t__ MT_SPIDER ; 
 scalar_t__ P_CheckSight (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  P_LookForPlayers (TYPE_4__*,int) ; 
 int P_Random () ; 
 int /*<<< orphan*/  P_SetMobjState (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_StartSound (TYPE_4__*,int) ; 
#define  sfx_bgsit1 132 
#define  sfx_bgsit2 131 
#define  sfx_posit1 130 
#define  sfx_posit2 129 
#define  sfx_posit3 128 

void A_Look (mobj_t* actor)
{
    mobj_t*	targ;
	
    actor->threshold = 0;	// any shot will wake up
    targ = actor->subsector->sector->soundtarget;

    if (targ
	&& (targ->flags & MF_SHOOTABLE) )
    {
	actor->target = targ;

	if ( actor->flags & MF_AMBUSH )
	{
	    if (P_CheckSight (actor, actor->target))
		goto seeyou;
	}
	else
	    goto seeyou;
    }
	
	
    if (!P_LookForPlayers (actor, false) )
	return;
		
    // go into chase state
  seeyou:
    if (actor->info->seesound)
    {
	int		sound;
		
	switch (actor->info->seesound)
	{
	  case sfx_posit1:
	  case sfx_posit2:
	  case sfx_posit3:
	    sound = sfx_posit1+P_Random()%3;
	    break;

	  case sfx_bgsit1:
	  case sfx_bgsit2:
	    sound = sfx_bgsit1+P_Random()%2;
	    break;

	  default:
	    sound = actor->info->seesound;
	    break;
	}

	if (actor->type==MT_SPIDER
	    || actor->type == MT_CYBORG)
	{
	    // full volume
	    S_StartSound (NULL, sound);
	}
	else
	    S_StartSound (actor, sound);
    }

    P_SetMobjState (actor, actor->info->seestate);
}