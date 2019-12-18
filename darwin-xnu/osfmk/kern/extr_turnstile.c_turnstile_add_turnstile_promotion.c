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
struct turnstile {int /*<<< orphan*/  ts_waitq; scalar_t__ ts_inheritor; int /*<<< orphan*/  ts_priority; int /*<<< orphan*/  ts_inheritor_links; int /*<<< orphan*/  ts_inheritor_queue; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRIORITY_QUEUE_SCHED_PRI_MAX_HEAP_COMPARE ; 
 int TSU_BOOST_ARG ; 
 int TSU_NO_INHERITOR ; 
 int TSU_NO_PRI_CHANGE_NEEDED ; 
 int TSU_TURNSTILE_ARG ; 
 int /*<<< orphan*/  TURNSTILE_ADDED_TO_TURNSTILE_HEAP ; 
 int TURNSTILE_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TURNSTILE_HEAP_OPERATIONS ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE_OR_PERM (struct turnstile*) ; 
 int /*<<< orphan*/  priority_queue_entry_init (int /*<<< orphan*/ *) ; 
 scalar_t__ priority_queue_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turnstile_recompute_priority_locked (struct turnstile*) ; 
 int /*<<< orphan*/  turnstile_stats_update (int,int,struct turnstile*) ; 
 int /*<<< orphan*/  waitq_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitq_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static boolean_t
turnstile_add_turnstile_promotion(
	struct turnstile *dst_turnstile,
	struct turnstile *src_turnstile)
{
	boolean_t needs_update = FALSE;

	/* Update the pairing heap */
	waitq_lock(&dst_turnstile->ts_waitq);

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
		(TURNSTILE_CODE(TURNSTILE_HEAP_OPERATIONS, (TURNSTILE_ADDED_TO_TURNSTILE_HEAP))) | DBG_FUNC_NONE,
		VM_KERNEL_UNSLIDE_OR_PERM(dst_turnstile),
		VM_KERNEL_UNSLIDE_OR_PERM(src_turnstile),
		src_turnstile->ts_priority, 0, 0);

	priority_queue_entry_init(&(src_turnstile->ts_inheritor_links));
	if (priority_queue_insert(&dst_turnstile->ts_inheritor_queue,
			&src_turnstile->ts_inheritor_links, src_turnstile->ts_priority,
			PRIORITY_QUEUE_SCHED_PRI_MAX_HEAP_COMPARE)) {
		/* Update dst turnstile priority */
		needs_update = turnstile_recompute_priority_locked(dst_turnstile);
	}

	/* Update turnstile stats */
	if (!needs_update) {
		turnstile_stats_update(1,
			(dst_turnstile->ts_inheritor ? TSU_NO_PRI_CHANGE_NEEDED : TSU_NO_INHERITOR) |
			TSU_TURNSTILE_ARG | TSU_BOOST_ARG, src_turnstile);
	}

	waitq_unlock(&dst_turnstile->ts_waitq);
	return needs_update;
}