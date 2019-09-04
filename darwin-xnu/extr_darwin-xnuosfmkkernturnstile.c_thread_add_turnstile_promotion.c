#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
struct turnstile {int /*<<< orphan*/  ts_priority; int /*<<< orphan*/  ts_inheritor_links; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_8__ {int /*<<< orphan*/  inheritor_queue; } ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRIORITY_QUEUE_SCHED_PRI_MAX_HEAP_COMPARE ; 
 int TSU_BOOST_ARG ; 
 int TSU_TURNSTILE_ARG ; 
 int /*<<< orphan*/  TURNSTILE_ADDED_TO_THREAD_HEAP ; 
 int TURNSTILE_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TURNSTILE_HEAP_OPERATIONS ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE_OR_PERM (struct turnstile*) ; 
 int /*<<< orphan*/  priority_queue_entry_init (int /*<<< orphan*/ *) ; 
 scalar_t__ priority_queue_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int thread_get_update_flags_for_turnstile_propagation_stoppage (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_recompute_user_promotion_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_tid (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  turnstile_stats_update (int,int,struct turnstile*) ; 

__attribute__((used)) static boolean_t
thread_add_turnstile_promotion(
	thread_t thread,
	struct turnstile *turnstile)
{
	boolean_t needs_update = FALSE;

	/* Update the pairing heap */
	thread_lock(thread);

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
		(TURNSTILE_CODE(TURNSTILE_HEAP_OPERATIONS, (TURNSTILE_ADDED_TO_THREAD_HEAP))) | DBG_FUNC_NONE,
		thread_tid(thread),
		VM_KERNEL_UNSLIDE_OR_PERM(turnstile),
		turnstile->ts_priority, 0, 0);

	priority_queue_entry_init(&(turnstile->ts_inheritor_links));
	if (priority_queue_insert(&thread->inheritor_queue,
			&turnstile->ts_inheritor_links, turnstile->ts_priority,
			PRIORITY_QUEUE_SCHED_PRI_MAX_HEAP_COMPARE)) {
		/* Update thread priority */
		needs_update = thread_recompute_user_promotion_locked(thread);
	}

	/* Update turnstile stats */
	if (!needs_update) {
		turnstile_stats_update(1,
			thread_get_update_flags_for_turnstile_propagation_stoppage(thread) |
			TSU_TURNSTILE_ARG | TSU_BOOST_ARG,
			turnstile);
	}

	thread_unlock(thread);
	return needs_update;
}