#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pending_commands; } ;
struct cardstate {int mode; int channels; int commands_pending; TYPE_1__* bcs; int /*<<< orphan*/  mstate; TYPE_2__ at_state; } ;
struct at_state_t {int pending_commands; } ;
struct TYPE_3__ {struct at_state_t at_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MS_UNINITIALIZED ; 
 int PC_CID ; 
 int /*<<< orphan*/  PC_INIT ; 
 int PC_NOCID ; 
 int /*<<< orphan*/  gigaset_free_channels (struct cardstate*) ; 

__attribute__((used)) static void init_failed(struct cardstate *cs, int mode)
{
	int i;
	struct at_state_t *at_state;

	cs->at_state.pending_commands &= ~PC_INIT;
	cs->mode = mode;
	cs->mstate = MS_UNINITIALIZED;
	gigaset_free_channels(cs);
	for (i = 0; i < cs->channels; ++i) {
		at_state = &cs->bcs[i].at_state;
		if (at_state->pending_commands & PC_CID) {
			at_state->pending_commands &= ~PC_CID;
			at_state->pending_commands |= PC_NOCID;
			cs->commands_pending = 1;
		}
	}
}