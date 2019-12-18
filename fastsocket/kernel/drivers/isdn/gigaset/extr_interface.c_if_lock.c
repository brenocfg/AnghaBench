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
struct cardstate {scalar_t__ mstate; int control_state; int waiting; int cmd_result; int /*<<< orphan*/  waitqueue; int /*<<< orphan*/  at_state; TYPE_1__* ops; scalar_t__ connected; int /*<<< orphan*/  minor_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_line_ctrl ) (struct cardstate*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* baud_rate ) (struct cardstate*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_modem_ctrl ) (struct cardstate*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  B115200 ; 
 int /*<<< orphan*/  CS8 ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int /*<<< orphan*/  DEBUG_IF ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_IF_LOCK ; 
 scalar_t__ MS_LOCKED ; 
 int TIOCM_DTR ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gigaset_add_event (struct cardstate*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gigaset_schedule_event (struct cardstate*) ; 
 int /*<<< orphan*/  stub1 (struct cardstate*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct cardstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct cardstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int if_lock(struct cardstate *cs, int *arg)
{
	int cmd = *arg;

	gig_dbg(DEBUG_IF, "%u: if_lock (%d)", cs->minor_index, cmd);

	if (cmd > 1)
		return -EINVAL;

	if (cmd < 0) {
		*arg = cs->mstate == MS_LOCKED;
		return 0;
	}

	if (!cmd && cs->mstate == MS_LOCKED && cs->connected) {
		cs->ops->set_modem_ctrl(cs, 0, TIOCM_DTR|TIOCM_RTS);
		cs->ops->baud_rate(cs, B115200);
		cs->ops->set_line_ctrl(cs, CS8);
		cs->control_state = TIOCM_DTR|TIOCM_RTS;
	}

	cs->waiting = 1;
	if (!gigaset_add_event(cs, &cs->at_state, EV_IF_LOCK,
			       NULL, cmd, NULL)) {
		cs->waiting = 0;
		return -ENOMEM;
	}

	gig_dbg(DEBUG_CMD, "scheduling IF_LOCK");
	gigaset_schedule_event(cs);

	wait_event(cs->waitqueue, !cs->waiting);

	if (cs->cmd_result >= 0) {
		*arg = cs->cmd_result;
		return 0;
	}

	return cs->cmd_result;
}