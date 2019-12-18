#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfs4_state {int state; TYPE_1__* owner; int /*<<< orphan*/  open_states; } ;
typedef  int fmode_t ;
struct TYPE_2__ {int /*<<< orphan*/  so_states; } ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
nfs4_state_set_mode_locked(struct nfs4_state *state, fmode_t fmode)
{
	if (state->state == fmode)
		return;
	/* NB! List reordering - see the reclaim code for why.  */
	if ((fmode & FMODE_WRITE) != (state->state & FMODE_WRITE)) {
		if (fmode & FMODE_WRITE)
			list_move(&state->open_states, &state->owner->so_states);
		else
			list_move_tail(&state->open_states, &state->owner->so_states);
	}
	state->state = fmode;
}