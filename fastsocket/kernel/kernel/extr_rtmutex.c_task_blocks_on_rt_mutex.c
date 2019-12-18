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
struct task_struct {int /*<<< orphan*/  pi_lock; struct rt_mutex_waiter* pi_blocked_on; int /*<<< orphan*/  pi_waiters; int /*<<< orphan*/  prio; } ;
struct rt_mutex_waiter {int /*<<< orphan*/  pi_list_entry; int /*<<< orphan*/  list_entry; struct rt_mutex* lock; struct task_struct* task; } ;
struct rt_mutex {int /*<<< orphan*/  wait_lock; int /*<<< orphan*/  wait_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rt_mutex_adjust_prio (struct task_struct*) ; 
 scalar_t__ debug_rt_mutex_detect_deadlock (struct rt_mutex_waiter*,int) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  plist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plist_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plist_node_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rt_mutex_adjust_prio_chain (struct task_struct*,int,struct rt_mutex*,struct rt_mutex_waiter*,struct task_struct*) ; 
 scalar_t__ rt_mutex_has_waiters (struct rt_mutex*) ; 
 struct task_struct* rt_mutex_owner (struct rt_mutex*) ; 
 struct rt_mutex_waiter* rt_mutex_top_waiter (struct rt_mutex*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int task_blocks_on_rt_mutex(struct rt_mutex *lock,
				   struct rt_mutex_waiter *waiter,
				   struct task_struct *task,
				   int detect_deadlock)
{
	struct task_struct *owner = rt_mutex_owner(lock);
	struct rt_mutex_waiter *top_waiter = waiter;
	unsigned long flags;
	int chain_walk = 0, res;

	spin_lock_irqsave(&task->pi_lock, flags);
	__rt_mutex_adjust_prio(task);
	waiter->task = task;
	waiter->lock = lock;
	plist_node_init(&waiter->list_entry, task->prio);
	plist_node_init(&waiter->pi_list_entry, task->prio);

	/* Get the top priority waiter on the lock */
	if (rt_mutex_has_waiters(lock))
		top_waiter = rt_mutex_top_waiter(lock);
	plist_add(&waiter->list_entry, &lock->wait_list);

	task->pi_blocked_on = waiter;

	spin_unlock_irqrestore(&task->pi_lock, flags);

	if (waiter == rt_mutex_top_waiter(lock)) {
		spin_lock_irqsave(&owner->pi_lock, flags);
		plist_del(&top_waiter->pi_list_entry, &owner->pi_waiters);
		plist_add(&waiter->pi_list_entry, &owner->pi_waiters);

		__rt_mutex_adjust_prio(owner);
		if (owner->pi_blocked_on)
			chain_walk = 1;
		spin_unlock_irqrestore(&owner->pi_lock, flags);
	}
	else if (debug_rt_mutex_detect_deadlock(waiter, detect_deadlock))
		chain_walk = 1;

	if (!chain_walk)
		return 0;

	/*
	 * The owner can't disappear while holding a lock,
	 * so the owner struct is protected by wait_lock.
	 * Gets dropped in rt_mutex_adjust_prio_chain()!
	 */
	get_task_struct(owner);

	spin_unlock(&lock->wait_lock);

	res = rt_mutex_adjust_prio_chain(owner, detect_deadlock, lock, waiter,
					 task);

	spin_lock(&lock->wait_lock);

	return res;
}