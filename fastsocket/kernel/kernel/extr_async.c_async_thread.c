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
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HZ ; 
 int /*<<< orphan*/  MAX_THREADS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  async_new ; 
 int /*<<< orphan*/  async_pending ; 
 int /*<<< orphan*/  atomic_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ need_resched () ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  run_one_entry () ; 
 int /*<<< orphan*/  schedule () ; 
 int schedule_timeout (int) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_count ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  wq ; 

__attribute__((used)) static int async_thread(void *unused)
{
	DECLARE_WAITQUEUE(wq, current);
	add_wait_queue(&async_new, &wq);

	while (!kthread_should_stop()) {
		int ret = HZ;
		/*
		 * check the list head without lock.. false positives
		 * are dealt with inside run_one_entry() while holding
		 * the lock.
		 */
		rmb();
		if (need_resched())
			schedule();

		if (!list_empty(&async_pending))
			run_one_entry();
		else {
			set_current_state(TASK_INTERRUPTIBLE);
			ret = schedule_timeout(HZ);
		}

		if (ret == 0) {
			/*
			 * we timed out, this means we as thread are redundant.
			 * we sign off and die, but we to avoid any races there
			 * is a last-straw check to see if work snuck in.
			 */
			atomic_dec(&thread_count);
			wmb(); /* manager must see our departure first */
			if (list_empty(&async_pending))
				break;
			/*
			 * woops work came in between us timing out and us
			 * signing off; we need to stay alive and keep working.
			 */
			if (!atomic_add_unless(&thread_count, 1, MAX_THREADS))
				/*
				 * The thread manager raced in and created a new thread
				 * While we were checking list empty
				 */
				break;
		}
	}
	remove_wait_queue(&async_new, &wq);

	return 0;
}