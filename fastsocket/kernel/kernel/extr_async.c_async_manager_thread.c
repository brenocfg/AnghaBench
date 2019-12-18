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
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MAX_THREADS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  async_new ; 
 int /*<<< orphan*/  async_thread ; 
 int /*<<< orphan*/  atomic_add_unless (int /*<<< orphan*/ *,int,int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  entry_count ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_count ; 
 int /*<<< orphan*/  wq ; 

__attribute__((used)) static int async_manager_thread(void *unused)
{
	DECLARE_WAITQUEUE(wq, current);
	add_wait_queue(&async_new, &wq);

	while (!kthread_should_stop()) {
		int tc, ec;

		set_current_state(TASK_INTERRUPTIBLE);

		tc = atomic_read(&thread_count);
		rmb();
		ec = atomic_read(&entry_count);

		while (tc < ec && tc < MAX_THREADS) {
			if (IS_ERR(kthread_run(async_thread, NULL, "async/%i",
					       tc))) {
				msleep(100);
				continue;
			}
			if (!atomic_add_unless(&thread_count, 1, MAX_THREADS))
				/*
				 * One of the exiting workers decided to stick around
				 */
				break;
			tc++;
		}

		schedule();
	}
	remove_wait_queue(&async_new, &wq);

	return 0;
}