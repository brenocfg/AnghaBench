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
struct rt_mutex_waiter {int task; } ;
struct rt_mutex {int /*<<< orphan*/  wait_lock; } ;
struct hrtimer_sleeper {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int __rt_mutex_slowlock (struct rt_mutex*,int /*<<< orphan*/ ,struct hrtimer_sleeper*,struct rt_mutex_waiter*,int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  fixup_rt_mutex_waiters (struct rt_mutex*) ; 
 int /*<<< orphan*/  remove_waiter (struct rt_mutex*,struct rt_mutex_waiter*) ; 
 int /*<<< orphan*/  rt_mutex_adjust_prio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int rt_mutex_finish_proxy_lock(struct rt_mutex *lock,
			       struct hrtimer_sleeper *to,
			       struct rt_mutex_waiter *waiter,
			       int detect_deadlock)
{
	int ret;

	spin_lock(&lock->wait_lock);

	set_current_state(TASK_INTERRUPTIBLE);

	ret = __rt_mutex_slowlock(lock, TASK_INTERRUPTIBLE, to, waiter,
				  detect_deadlock);

	set_current_state(TASK_RUNNING);

	if (unlikely(waiter->task))
		remove_waiter(lock, waiter);

	/*
	 * try_to_take_rt_mutex() sets the waiter bit unconditionally. We might
	 * have to fix that up.
	 */
	fixup_rt_mutex_waiters(lock);

	spin_unlock(&lock->wait_lock);

	/*
	 * Readjust priority, when we did not get the lock. We might have been
	 * the pending owner and boosted. Since we did not take the lock, the
	 * PI boost has to go.
	 */
	if (unlikely(ret))
		rt_mutex_adjust_prio(current);

	return ret;
}