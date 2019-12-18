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
struct task_struct {int /*<<< orphan*/  pi_lock; int /*<<< orphan*/ * pi_blocked_on; int /*<<< orphan*/  pi_waiters; } ;
struct rt_mutex_waiter {int /*<<< orphan*/  pi_list_entry; int /*<<< orphan*/ * task; int /*<<< orphan*/  list_entry; } ;
struct rt_mutex {int /*<<< orphan*/  wait_lock; int /*<<< orphan*/  wait_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __rt_mutex_adjust_prio (struct task_struct*) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  plist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plist_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plist_node_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_mutex_adjust_prio_chain (struct task_struct*,int /*<<< orphan*/ ,struct rt_mutex*,int /*<<< orphan*/ *,struct task_struct*) ; 
 scalar_t__ rt_mutex_has_waiters (struct rt_mutex*) ; 
 struct task_struct* rt_mutex_owner (struct rt_mutex*) ; 
 struct rt_mutex_waiter* rt_mutex_top_waiter (struct rt_mutex*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void remove_waiter(struct rt_mutex *lock,
			  struct rt_mutex_waiter *waiter)
{
	int first = (waiter == rt_mutex_top_waiter(lock));
	struct task_struct *owner = rt_mutex_owner(lock);
	unsigned long flags;
	int chain_walk = 0;

	spin_lock_irqsave(&current->pi_lock, flags);
	plist_del(&waiter->list_entry, &lock->wait_list);
	waiter->task = NULL;
	current->pi_blocked_on = NULL;
	spin_unlock_irqrestore(&current->pi_lock, flags);

	if (first && owner != current) {

		spin_lock_irqsave(&owner->pi_lock, flags);

		plist_del(&waiter->pi_list_entry, &owner->pi_waiters);

		if (rt_mutex_has_waiters(lock)) {
			struct rt_mutex_waiter *next;

			next = rt_mutex_top_waiter(lock);
			plist_add(&next->pi_list_entry, &owner->pi_waiters);
		}
		__rt_mutex_adjust_prio(owner);

		if (owner->pi_blocked_on)
			chain_walk = 1;

		spin_unlock_irqrestore(&owner->pi_lock, flags);
	}

	WARN_ON(!plist_node_empty(&waiter->pi_list_entry));

	if (!chain_walk)
		return;

	/* gets dropped in rt_mutex_adjust_prio_chain()! */
	get_task_struct(owner);

	spin_unlock(&lock->wait_lock);

	rt_mutex_adjust_prio_chain(owner, 0, lock, NULL, current);

	spin_lock(&lock->wait_lock);
}