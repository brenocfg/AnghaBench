#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cardstate {int waiting; int /*<<< orphan*/  mutex; int /*<<< orphan*/  waitqueue; int /*<<< orphan*/  at_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CMD ; 
 int /*<<< orphan*/  EV_STOP ; 
 int /*<<< orphan*/  cleanup_cs (struct cardstate*) ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gigaset_add_event (struct cardstate*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gigaset_schedule_event (struct cardstate*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void gigaset_stop(struct cardstate *cs)
{
	mutex_lock(&cs->mutex);

	cs->waiting = 1;

	if (!gigaset_add_event(cs, &cs->at_state, EV_STOP, NULL, 0, NULL)) {
		//FIXME what should we do?
		goto exit;
	}

	gig_dbg(DEBUG_CMD, "scheduling STOP");
	gigaset_schedule_event(cs);

	wait_event(cs->waitqueue, !cs->waiting);

	cleanup_cs(cs);

exit:
	mutex_unlock(&cs->mutex);
}