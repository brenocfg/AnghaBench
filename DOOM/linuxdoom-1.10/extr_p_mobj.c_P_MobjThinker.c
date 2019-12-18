#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ acv; } ;
struct TYPE_11__ {TYPE_1__ function; } ;
struct TYPE_13__ {int flags; scalar_t__ z; scalar_t__ floorz; int tics; int movecount; TYPE_3__* state; TYPE_2__ thinker; scalar_t__ momz; scalar_t__ momy; scalar_t__ momx; } ;
typedef  TYPE_4__ mobj_t ;
typedef  scalar_t__ actionf_v ;
struct TYPE_12__ {int /*<<< orphan*/  nextstate; } ;

/* Variables and functions */
 int MF_COUNTKILL ; 
 int MF_SKULLFLY ; 
 int /*<<< orphan*/  P_NightmareRespawn (TYPE_4__*) ; 
 int P_Random () ; 
 int /*<<< orphan*/  P_SetMobjState (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_XYMovement (TYPE_4__*) ; 
 int /*<<< orphan*/  P_ZMovement (TYPE_4__*) ; 
 int leveltime ; 
 int /*<<< orphan*/  respawnmonsters ; 

void P_MobjThinker (mobj_t* mobj)
{
    // momentum movement
    if (mobj->momx
	|| mobj->momy
	|| (mobj->flags&MF_SKULLFLY) )
    {
	P_XYMovement (mobj);

	// FIXME: decent NOP/NULL/Nil function pointer please.
	if (mobj->thinker.function.acv == (actionf_v) (-1))
	    return;		// mobj was removed
    }
    if ( (mobj->z != mobj->floorz)
	 || mobj->momz )
    {
	P_ZMovement (mobj);
	
	// FIXME: decent NOP/NULL/Nil function pointer please.
	if (mobj->thinker.function.acv == (actionf_v) (-1))
	    return;		// mobj was removed
    }

    
    // cycle through states,
    // calling action functions at transitions
    if (mobj->tics != -1)
    {
	mobj->tics--;
		
	// you can cycle through multiple states in a tic
	if (!mobj->tics)
	    if (!P_SetMobjState (mobj, mobj->state->nextstate) )
		return;		// freed itself
    }
    else
    {
	// check for nightmare respawn
	if (! (mobj->flags & MF_COUNTKILL) )
	    return;

	if (!respawnmonsters)
	    return;

	mobj->movecount++;

	if (mobj->movecount < 12*35)
	    return;

	if ( leveltime&31 )
	    return;

	if (P_Random () > 4)
	    return;

	P_NightmareRespawn (mobj);
    }

}