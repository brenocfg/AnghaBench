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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  fake_signal_wake_up (struct task_struct*) ; 
 int /*<<< orphan*/  freezing (struct task_struct*) ; 
 scalar_t__ frozen (struct task_struct*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  set_freeze_flag (struct task_struct*) ; 
 scalar_t__ should_send_signal (struct task_struct*) ; 
 int /*<<< orphan*/  signal_pending (struct task_struct*) ; 
 int /*<<< orphan*/  wake_up_state (struct task_struct*,int /*<<< orphan*/ ) ; 

bool freeze_task(struct task_struct *p, bool sig_only)
{
	/*
	 * We first check if the task is freezing and next if it has already
	 * been frozen to avoid the race with frozen_process() which first marks
	 * the task as frozen and next clears its TIF_FREEZE.
	 */
	if (!freezing(p)) {
		rmb();
		if (frozen(p))
			return false;

		if (!sig_only || should_send_signal(p))
			set_freeze_flag(p);
		else
			return false;
	}

	if (should_send_signal(p)) {
		if (!signal_pending(p))
			fake_signal_wake_up(p);
	} else if (sig_only) {
		return false;
	} else {
		wake_up_state(p, TASK_INTERRUPTIBLE);
	}

	return true;
}