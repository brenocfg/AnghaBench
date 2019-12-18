#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int reactiontime; int y; int momy; TYPE_1__* state; struct TYPE_9__* target; } ;
typedef  TYPE_2__ mobj_t ;
struct TYPE_8__ {int tics; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_SPAWNSHOT ; 
 TYPE_2__* P_SpawnMissile (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_StartSound (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t braintargeton ; 
 TYPE_2__** braintargets ; 
 scalar_t__ gameskill ; 
 size_t numbraintargets ; 
 int /*<<< orphan*/  sfx_bospit ; 
 scalar_t__ sk_easy ; 

void A_BrainSpit (mobj_t*	mo)
{
    mobj_t*	targ;
    mobj_t*	newmobj;
    
    static int	easy = 0;
	
    easy ^= 1;
    if (gameskill <= sk_easy && (!easy))
	return;
		
    // shoot a cube at current target
    targ = braintargets[braintargeton];
    braintargeton = (braintargeton+1)%numbraintargets;

    // spawn brain missile
    newmobj = P_SpawnMissile (mo, targ, MT_SPAWNSHOT);
    newmobj->target = targ;
    newmobj->reactiontime =
	((targ->y - mo->y)/newmobj->momy) / newmobj->state->tics;

    S_StartSound(NULL, sfx_bospit);
}