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
struct task_struct {unsigned int lockdep_depth; struct held_lock* held_locks; int /*<<< orphan*/  curr_chain_key; } ;
struct lockdep_map {int dummy; } ;
struct held_lock {scalar_t__ irq_context; scalar_t__ references; int /*<<< orphan*/  acquire_ip; int /*<<< orphan*/  nest_lock; int /*<<< orphan*/  hardirqs_off; int /*<<< orphan*/  check; int /*<<< orphan*/  read; int /*<<< orphan*/  trylock; struct lockdep_map* instance; int /*<<< orphan*/  prev_chain_key; } ;
struct TYPE_2__ {int /*<<< orphan*/  subclass; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LOCKS_WARN_ON (int) ; 
 int /*<<< orphan*/  __lock_acquire (struct lockdep_map*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* hlock_class (struct held_lock*) ; 
 int /*<<< orphan*/  lock_release_holdtime (struct held_lock*) ; 
 scalar_t__ match_held_lock (struct held_lock*,struct lockdep_map*) ; 
 int print_unlock_inbalance_bug (struct task_struct*,struct lockdep_map*,unsigned long) ; 

__attribute__((used)) static int
lock_release_non_nested(struct task_struct *curr,
			struct lockdep_map *lock, unsigned long ip)
{
	struct held_lock *hlock, *prev_hlock;
	unsigned int depth;
	int i;

	/*
	 * Check whether the lock exists in the current stack
	 * of held locks:
	 */
	depth = curr->lockdep_depth;
	if (DEBUG_LOCKS_WARN_ON(!depth))
		return 0;

	prev_hlock = NULL;
	for (i = depth-1; i >= 0; i--) {
		hlock = curr->held_locks + i;
		/*
		 * We must not cross into another context:
		 */
		if (prev_hlock && prev_hlock->irq_context != hlock->irq_context)
			break;
		if (match_held_lock(hlock, lock))
			goto found_it;
		prev_hlock = hlock;
	}
	return print_unlock_inbalance_bug(curr, lock, ip);

found_it:
	if (hlock->instance == lock)
		lock_release_holdtime(hlock);

	if (hlock->references) {
		hlock->references--;
		if (hlock->references) {
			/*
			 * We had, and after removing one, still have
			 * references, the current lock stack is still
			 * valid. We're done!
			 */
			return 1;
		}
	}

	/*
	 * We have the right lock to unlock, 'hlock' points to it.
	 * Now we remove it from the stack, and add back the other
	 * entries (if any), recalculating the hash along the way:
	 */

	curr->lockdep_depth = i;
	curr->curr_chain_key = hlock->prev_chain_key;

	for (i++; i < depth; i++) {
		hlock = curr->held_locks + i;
		if (!__lock_acquire(hlock->instance,
			hlock_class(hlock)->subclass, hlock->trylock,
				hlock->read, hlock->check, hlock->hardirqs_off,
				hlock->nest_lock, hlock->acquire_ip,
				hlock->references))
			return 0;
	}

	if (DEBUG_LOCKS_WARN_ON(curr->lockdep_depth != depth - 1))
		return 0;
	return 1;
}