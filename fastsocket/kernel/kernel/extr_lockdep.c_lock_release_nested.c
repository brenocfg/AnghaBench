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
struct task_struct {int lockdep_depth; scalar_t__ curr_chain_key; struct held_lock* held_locks; } ;
struct lockdep_map {int dummy; } ;
struct held_lock {scalar_t__ prev_chain_key; scalar_t__ irq_context; scalar_t__ acquire_ip; scalar_t__ class_idx; scalar_t__ references; struct lockdep_map* instance; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LOCKS_WARN_ON (int) ; 
 int /*<<< orphan*/  lock_release_holdtime (struct held_lock*) ; 
 int lock_release_non_nested (struct task_struct*,struct lockdep_map*,unsigned long) ; 

__attribute__((used)) static int lock_release_nested(struct task_struct *curr,
			       struct lockdep_map *lock, unsigned long ip)
{
	struct held_lock *hlock;
	unsigned int depth;

	/*
	 * Pop off the top of the lock stack:
	 */
	depth = curr->lockdep_depth - 1;
	hlock = curr->held_locks + depth;

	/*
	 * Is the unlock non-nested:
	 */
	if (hlock->instance != lock || hlock->references)
		return lock_release_non_nested(curr, lock, ip);
	curr->lockdep_depth--;

	if (DEBUG_LOCKS_WARN_ON(!depth && (hlock->prev_chain_key != 0)))
		return 0;

	curr->curr_chain_key = hlock->prev_chain_key;

	lock_release_holdtime(hlock);

#ifdef CONFIG_DEBUG_LOCKDEP
	hlock->prev_chain_key = 0;
	hlock->class_idx = 0;
	hlock->acquire_ip = 0;
	hlock->irq_context = 0;
#endif
	return 1;
}