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
struct ib_fmr_pool {int /*<<< orphan*/  req_ser; int /*<<< orphan*/  flush_ser; int /*<<< orphan*/  flush_arg; int /*<<< orphan*/  (* flush_function ) (struct ib_fmr_pool*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  force_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_fmr_batch_release (struct ib_fmr_pool*) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ib_fmr_pool*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ib_fmr_cleanup_thread(void *pool_ptr)
{
	struct ib_fmr_pool *pool = pool_ptr;

	do {
		if (atomic_read(&pool->flush_ser) - atomic_read(&pool->req_ser) < 0) {
			ib_fmr_batch_release(pool);

			atomic_inc(&pool->flush_ser);
			wake_up_interruptible(&pool->force_wait);

			if (pool->flush_function)
				pool->flush_function(pool, pool->flush_arg);
		}

		set_current_state(TASK_INTERRUPTIBLE);
		if (atomic_read(&pool->flush_ser) - atomic_read(&pool->req_ser) >= 0 &&
		    !kthread_should_stop())
			schedule();
		__set_current_state(TASK_RUNNING);
	} while (!kthread_should_stop());

	return 0;
}