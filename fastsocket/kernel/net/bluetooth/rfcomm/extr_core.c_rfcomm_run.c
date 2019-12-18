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

/* Variables and functions */
 int /*<<< orphan*/  BDADDR_ANY ; 
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  RFCOMM_SCHED_WAKEUP ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  rfcomm_add_listener (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_event ; 
 int /*<<< orphan*/  rfcomm_kill_listener () ; 
 int /*<<< orphan*/  rfcomm_process_sessions () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rfcomm_run(void *unused)
{
	BT_DBG("");

	set_user_nice(current, -10);

	rfcomm_add_listener(BDADDR_ANY);

	while (!kthread_should_stop()) {
		set_current_state(TASK_INTERRUPTIBLE);
		if (!test_bit(RFCOMM_SCHED_WAKEUP, &rfcomm_event)) {
			/* No pending events. Let's sleep.
			 * Incoming connections and data will wake us up. */
			schedule();
		}
		set_current_state(TASK_RUNNING);

		/* Process stuff */
		clear_bit(RFCOMM_SCHED_WAKEUP, &rfcomm_event);
		rfcomm_process_sessions();
	}

	rfcomm_kill_listener();

	return 0;
}