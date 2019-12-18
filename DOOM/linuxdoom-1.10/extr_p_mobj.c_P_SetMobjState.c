#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t statenum_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* acp1 ) (TYPE_3__*) ;} ;
struct TYPE_9__ {size_t nextstate; TYPE_1__ action; int /*<<< orphan*/  frame; int /*<<< orphan*/  sprite; int /*<<< orphan*/  tics; } ;
typedef  TYPE_2__ state_t ;
struct TYPE_10__ {int /*<<< orphan*/  frame; int /*<<< orphan*/  sprite; int /*<<< orphan*/  tics; TYPE_2__* state; } ;
typedef  TYPE_3__ mobj_t ;
typedef  int boolean ;

/* Variables and functions */
 int /*<<< orphan*/  P_RemoveMobj (TYPE_3__*) ; 
 size_t S_NULL ; 
 TYPE_2__* states ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

boolean
P_SetMobjState
( mobj_t*	mobj,
  statenum_t	state )
{
    state_t*	st;

    do
    {
	if (state == S_NULL)
	{
	    mobj->state = (state_t *) S_NULL;
	    P_RemoveMobj (mobj);
	    return false;
	}

	st = &states[state];
	mobj->state = st;
	mobj->tics = st->tics;
	mobj->sprite = st->sprite;
	mobj->frame = st->frame;

	// Modified handling.
	// Call action functions when the state is set
	if (st->action.acp1)		
	    st->action.acp1(mobj);	
	
	state = st->nextstate;
    } while (!mobj->tics);
				
    return true;
}