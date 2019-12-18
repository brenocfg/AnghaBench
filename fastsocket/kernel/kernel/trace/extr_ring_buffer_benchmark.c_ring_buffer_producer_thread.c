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
 int HZ ; 
 int SLEEP_TIME ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer ; 
 scalar_t__ consumer ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ kill_test ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  read_start ; 
 int /*<<< orphan*/  ring_buffer_producer () ; 
 int /*<<< orphan*/  ring_buffer_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout (int) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  trace_printk (char*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_to_die () ; 
 int /*<<< orphan*/  wake_up_process (scalar_t__) ; 

__attribute__((used)) static int ring_buffer_producer_thread(void *arg)
{
	init_completion(&read_start);

	while (!kthread_should_stop() && !kill_test) {
		ring_buffer_reset(buffer);

		if (consumer) {
			smp_wmb();
			wake_up_process(consumer);
			wait_for_completion(&read_start);
		}

		ring_buffer_producer();

		trace_printk("Sleeping for 10 secs\n");
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_timeout(HZ * SLEEP_TIME);
		__set_current_state(TASK_RUNNING);
	}

	if (kill_test)
		wait_to_die();

	return 0;
}