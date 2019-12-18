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
struct rt_mutex_waiter {int /*<<< orphan*/  task; } ;
struct rt_mutex {int /*<<< orphan*/  wait_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_rt_mutex_lock (struct rt_mutex*) ; 
 int /*<<< orphan*/  debug_rt_mutex_print_deadlock (struct rt_mutex_waiter*) ; 
 int /*<<< orphan*/  mark_rt_mutex_waiters (struct rt_mutex*) ; 
 int /*<<< orphan*/  rt_mutex_deadlock_account_lock (struct rt_mutex*,struct task_struct*) ; 
 int /*<<< orphan*/  rt_mutex_owner (struct rt_mutex*) ; 
 int /*<<< orphan*/  rt_mutex_set_owner (struct rt_mutex*,struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int task_blocks_on_rt_mutex (struct rt_mutex*,struct rt_mutex_waiter*,struct task_struct*,int) ; 
 scalar_t__ try_to_steal_lock (struct rt_mutex*,struct task_struct*) ; 

int rt_mutex_start_proxy_lock(struct rt_mutex *lock,
			      struct rt_mutex_waiter *waiter,
			      struct task_struct *task, int detect_deadlock)
{
	int ret;

	spin_lock(&lock->wait_lock);

	mark_rt_mutex_waiters(lock);

	if (!rt_mutex_owner(lock) || try_to_steal_lock(lock, task)) {
		/* We got the lock for task. */
		debug_rt_mutex_lock(lock);
		rt_mutex_set_owner(lock, task, 0);
		spin_unlock(&lock->wait_lock);
		rt_mutex_deadlock_account_lock(lock, task);
		return 1;
	}

	ret = task_blocks_on_rt_mutex(lock, waiter, task, detect_deadlock);

	if (ret && !waiter->task) {
		/*
		 * Reset the return value. We might have
		 * returned with -EDEADLK and the owner
		 * released the lock while we were walking the
		 * pi chain.  Let the waiter sort it out.
		 */
		ret = 0;
	}
	spin_unlock(&lock->wait_lock);

	debug_rt_mutex_print_deadlock(waiter);

	return ret;
}