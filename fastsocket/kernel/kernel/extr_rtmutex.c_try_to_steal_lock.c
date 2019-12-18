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
struct task_struct {scalar_t__ prio; int /*<<< orphan*/  pi_lock; int /*<<< orphan*/  pi_waiters; } ;
struct rt_mutex_waiter {int /*<<< orphan*/  pi_list_entry; struct task_struct* task; } ;
struct rt_mutex {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rt_mutex_adjust_prio (struct task_struct*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  plist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plist_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_mutex_has_waiters (struct rt_mutex*) ; 
 struct task_struct* rt_mutex_owner (struct rt_mutex*) ; 
 int /*<<< orphan*/  rt_mutex_owner_pending (struct rt_mutex*) ; 
 struct rt_mutex_waiter* rt_mutex_top_waiter (struct rt_mutex*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline int try_to_steal_lock(struct rt_mutex *lock,
				    struct task_struct *task)
{
	struct task_struct *pendowner = rt_mutex_owner(lock);
	struct rt_mutex_waiter *next;
	unsigned long flags;

	if (!rt_mutex_owner_pending(lock))
		return 0;

	if (pendowner == task)
		return 1;

	spin_lock_irqsave(&pendowner->pi_lock, flags);
	if (task->prio >= pendowner->prio) {
		spin_unlock_irqrestore(&pendowner->pi_lock, flags);
		return 0;
	}

	/*
	 * Check if a waiter is enqueued on the pending owners
	 * pi_waiters list. Remove it and readjust pending owners
	 * priority.
	 */
	if (likely(!rt_mutex_has_waiters(lock))) {
		spin_unlock_irqrestore(&pendowner->pi_lock, flags);
		return 1;
	}

	/* No chain handling, pending owner is not blocked on anything: */
	next = rt_mutex_top_waiter(lock);
	plist_del(&next->pi_list_entry, &pendowner->pi_waiters);
	__rt_mutex_adjust_prio(pendowner);
	spin_unlock_irqrestore(&pendowner->pi_lock, flags);

	/*
	 * We are going to steal the lock and a waiter was
	 * enqueued on the pending owners pi_waiters queue. So
	 * we have to enqueue this waiter into
	 * task->pi_waiters list. This covers the case,
	 * where task is boosted because it holds another
	 * lock and gets unboosted because the booster is
	 * interrupted, so we would delay a waiter with higher
	 * priority as task->normal_prio.
	 *
	 * Note: in the rare case of a SCHED_OTHER task changing
	 * its priority and thus stealing the lock, next->task
	 * might be task:
	 */
	if (likely(next->task != task)) {
		spin_lock_irqsave(&task->pi_lock, flags);
		plist_add(&next->pi_list_entry, &task->pi_waiters);
		__rt_mutex_adjust_prio(task);
		spin_unlock_irqrestore(&task->pi_lock, flags);
	}
	return 1;
}