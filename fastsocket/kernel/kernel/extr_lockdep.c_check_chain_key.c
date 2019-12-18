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
typedef  scalar_t__ u64 ;
struct task_struct {unsigned int lockdep_depth; scalar_t__ curr_chain_key; struct held_lock* held_locks; } ;
struct held_lock {scalar_t__ prev_chain_key; int class_idx; scalar_t__ irq_context; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LOCKS_WARN_ON (int) ; 
 unsigned int MAX_LOCKDEP_KEYS ; 
 int /*<<< orphan*/  WARN (int,char*,unsigned int,unsigned int,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  debug_locks_off () ; 
 scalar_t__ iterate_chain_key (scalar_t__,unsigned int) ; 

__attribute__((used)) static void check_chain_key(struct task_struct *curr)
{
#ifdef CONFIG_DEBUG_LOCKDEP
	struct held_lock *hlock, *prev_hlock = NULL;
	unsigned int i, id;
	u64 chain_key = 0;

	for (i = 0; i < curr->lockdep_depth; i++) {
		hlock = curr->held_locks + i;
		if (chain_key != hlock->prev_chain_key) {
			debug_locks_off();
			WARN(1, "hm#1, depth: %u [%u], %016Lx != %016Lx\n",
				curr->lockdep_depth, i,
				(unsigned long long)chain_key,
				(unsigned long long)hlock->prev_chain_key);
			return;
		}
		id = hlock->class_idx - 1;
		if (DEBUG_LOCKS_WARN_ON(id >= MAX_LOCKDEP_KEYS))
			return;

		if (prev_hlock && (prev_hlock->irq_context !=
							hlock->irq_context))
			chain_key = 0;
		chain_key = iterate_chain_key(chain_key, id);
		prev_hlock = hlock;
	}
	if (chain_key != curr->curr_chain_key) {
		debug_locks_off();
		WARN(1, "hm#2, depth: %u [%u], %016Lx != %016Lx\n",
			curr->lockdep_depth, i,
			(unsigned long long)chain_key,
			(unsigned long long)curr->curr_chain_key);
	}
#endif
}