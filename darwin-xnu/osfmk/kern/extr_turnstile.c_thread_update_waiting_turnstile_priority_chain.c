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
typedef  scalar_t__ uint32_t ;
typedef  int turnstile_stats_update_flags_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct turnstile {int /*<<< orphan*/  ts_waitq; scalar_t__ ts_inheritor; } ;
typedef  int boolean_t ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int FALSE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THREAD_NOT_WAITING_ON_TURNSTILE ; 
 int /*<<< orphan*/  THREAD_NULL ; 
 int TSU_NO_INHERITOR ; 
 int TSU_NO_PRI_CHANGE_NEEDED ; 
 int TSU_NO_TURNSTILE ; 
 int TSU_THREAD_ARG ; 
 int TURNSTILE_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TURNSTILE_HEAP_OPERATIONS ; 
 struct turnstile* TURNSTILE_NULL ; 
 int /*<<< orphan*/  TURNSTILE_UPDATE_STOPPED_BY_LIMIT ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE_OR_PERM (struct turnstile*) ; 
 int /*<<< orphan*/  thread_deallocate_safe (int /*<<< orphan*/ ) ; 
 struct turnstile* thread_get_waiting_turnstile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_reference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_tid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turnstile_deallocate_safe (struct turnstile*) ; 
 scalar_t__ turnstile_get_gencount (struct turnstile*) ; 
 int turnstile_max_hop ; 
 int turnstile_need_thread_promotion_update (struct turnstile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turnstile_reference (struct turnstile*) ; 
 int /*<<< orphan*/  turnstile_stats_update (int,int,int /*<<< orphan*/ ) ; 
 int turnstile_update_thread_promotion_locked (struct turnstile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitq_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitq_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
thread_update_waiting_turnstile_priority_chain(
	thread_t *in_thread,
	struct turnstile **out_turnstile,
	int thread_hop,
	int total_hop,
	turnstile_stats_update_flags_t tsu_flags)
{
	boolean_t needs_update = FALSE;
	thread_t thread = *in_thread;
	struct turnstile *waiting_turnstile = TURNSTILE_NULL;
	uint32_t turnstile_gencount;
	boolean_t first_update = !total_hop;

	*in_thread = THREAD_NULL;

	/* Check if thread waiting on a turnstile */
	waiting_turnstile = thread_get_waiting_turnstile(thread);

	if (waiting_turnstile == TURNSTILE_NULL || thread_hop > turnstile_max_hop) {
		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
			(TURNSTILE_CODE(TURNSTILE_HEAP_OPERATIONS,
			 (waiting_turnstile ? TURNSTILE_UPDATE_STOPPED_BY_LIMIT : THREAD_NOT_WAITING_ON_TURNSTILE)
			)) | DBG_FUNC_NONE,
			thread_tid(thread),
			turnstile_max_hop,
			thread_hop,
			VM_KERNEL_UNSLIDE_OR_PERM(waiting_turnstile), 0);
		turnstile_stats_update(total_hop + 1, TSU_NO_TURNSTILE |
			TSU_THREAD_ARG | tsu_flags, thread);
		thread_unlock(thread);
		return;
	}

	/* Check if the thread needs to update the waiting turnstile */
	needs_update = turnstile_need_thread_promotion_update(waiting_turnstile, thread);
	if (!needs_update && !first_update) {
		turnstile_stats_update(total_hop + 1, TSU_NO_PRI_CHANGE_NEEDED |
			TSU_THREAD_ARG | tsu_flags, thread);
		thread_unlock(thread);
		return;
	}

	/* take a reference on thread, turnstile and snapshot of gencount */
	turnstile_gencount = turnstile_get_gencount(waiting_turnstile);
	turnstile_reference(waiting_turnstile);
	thread_reference(thread);

	/* drop the thread lock and acquire the turnstile lock */
	thread_unlock(thread);
	waitq_lock(&waiting_turnstile->ts_waitq);
	thread_lock(thread);

	/* Check if the gencount matches and thread is still waiting on same turnstile */
	if (turnstile_gencount != turnstile_get_gencount(waiting_turnstile) ||
	    waiting_turnstile != thread_get_waiting_turnstile(thread)) {
		turnstile_stats_update(total_hop + 1, TSU_NO_PRI_CHANGE_NEEDED |
			TSU_THREAD_ARG | tsu_flags, thread);
		/* No updates required, bail out */
		thread_unlock(thread);
		waitq_unlock(&waiting_turnstile->ts_waitq);
		thread_deallocate_safe(thread);
		turnstile_deallocate_safe(waiting_turnstile);
		return;
	}

	/*
	 * The thread is waiting on the waiting_turnstile and we have thread lock,
	 * we can drop the thread and turnstile reference since its on waitq and
	 * it could not be removed from the waitq without the thread lock.
	 */
	thread_deallocate_safe(thread);
	turnstile_deallocate_safe(waiting_turnstile);

	/* adjust thread's position on turnstile waitq */
	needs_update = turnstile_update_thread_promotion_locked(waiting_turnstile, thread);

	/*
	 * Check if thread needs further priority propagation,
	 * since the first hop priority update was done in
	 * turnstile_update_inheritor, do not bailout if it is
	 * the first update as needs_update flag would evaluate to
	 * false for that case.
	 */
	if (!needs_update && !first_update) {
		turnstile_stats_update(total_hop + 1,
			(waiting_turnstile->ts_inheritor ? TSU_NO_PRI_CHANGE_NEEDED : TSU_NO_INHERITOR) |
			TSU_THREAD_ARG | tsu_flags, thread);
		thread_unlock(thread);
		waitq_unlock(&waiting_turnstile->ts_waitq);
		return;
	}

	/* drop the thread lock and update the turnstile */
	thread_unlock(thread);
	*out_turnstile = waiting_turnstile;
}