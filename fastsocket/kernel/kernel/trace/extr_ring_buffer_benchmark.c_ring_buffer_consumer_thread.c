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
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ kill_test ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  read_start ; 
 int /*<<< orphan*/  ring_buffer_consumer () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_to_die () ; 

__attribute__((used)) static int ring_buffer_consumer_thread(void *arg)
{
	while (!kthread_should_stop() && !kill_test) {
		complete(&read_start);

		ring_buffer_consumer();

		set_current_state(TASK_INTERRUPTIBLE);
		if (kthread_should_stop() || kill_test)
			break;

		schedule();
		__set_current_state(TASK_RUNNING);
	}
	__set_current_state(TASK_RUNNING);

	if (kill_test)
		wait_to_die();

	return 0;
}