#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int /*<<< orphan*/  pi_lock; int /*<<< orphan*/  pi_waiters; struct rt_mutex_waiter* pi_blocked_on; } ;
struct rt_mutex_waiter {int /*<<< orphan*/  pi_list_entry; struct rt_mutex* lock; struct task_struct* task; int /*<<< orphan*/  list_entry; } ;
struct rt_mutex {int /*<<< orphan*/  wait_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  pi_lock; int /*<<< orphan*/  pi_waiters; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_MUTEX_OWNER_PENDING ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  plist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plist_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rt_mutex_has_waiters (struct rt_mutex*) ; 
 int /*<<< orphan*/  rt_mutex_set_owner (struct rt_mutex*,struct task_struct*,int /*<<< orphan*/ ) ; 
 struct rt_mutex_waiter* rt_mutex_top_waiter (struct rt_mutex*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

__attribute__((used)) static void wakeup_next_waiter(struct rt_mutex *lock)
{
	struct rt_mutex_waiter *waiter;
	struct task_struct *pendowner;
	unsigned long flags;

	spin_lock_irqsave(&current->pi_lock, flags);

	waiter = rt_mutex_top_waiter(lock);
	plist_del(&waiter->list_entry, &lock->wait_list);

	/*
	 * Remove it from current->pi_waiters. We do not adjust a
	 * possible priority boost right now. We execute wakeup in the
	 * boosted mode and go back to normal after releasing
	 * lock->wait_lock.
	 */
	plist_del(&waiter->pi_list_entry, &current->pi_waiters);
	pendowner = waiter->task;
	waiter->task = NULL;

	rt_mutex_set_owner(lock, pendowner, RT_MUTEX_OWNER_PENDING);

	spin_unlock_irqrestore(&current->pi_lock, flags);

	/*
	 * Clear the pi_blocked_on variable and enqueue a possible
	 * waiter into the pi_waiters list of the pending owner. This
	 * prevents that in case the pending owner gets unboosted a
	 * waiter with higher priority than pending-owner->normal_prio
	 * is blocked on the unboosted (pending) owner.
	 */
	spin_lock_irqsave(&pendowner->pi_lock, flags);

	WARN_ON(!pendowner->pi_blocked_on);
	WARN_ON(pendowner->pi_blocked_on != waiter);
	WARN_ON(pendowner->pi_blocked_on->lock != lock);

	pendowner->pi_blocked_on = NULL;

	if (rt_mutex_has_waiters(lock)) {
		struct rt_mutex_waiter *next;

		next = rt_mutex_top_waiter(lock);
		plist_add(&next->pi_list_entry, &pendowner->pi_waiters);
	}
	spin_unlock_irqrestore(&pendowner->pi_lock, flags);

	wake_up_process(pendowner);
}