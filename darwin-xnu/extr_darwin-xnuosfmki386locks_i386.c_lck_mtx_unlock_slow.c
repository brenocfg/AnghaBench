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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int LCK_MTX_ILOCKED_MSK ; 
 int LCK_MTX_MLOCKED_MSK ; 
 int LCK_MTX_PROMOTED_MSK ; 
 int LCK_MTX_SPIN_MSK ; 
 int LCK_MTX_TAG_INDIRECT ; 
 scalar_t__ LCK_MTX_WAITER ; 
 int LCK_MTX_WAITERS_MSK ; 
 scalar_t__ __improbable (int) ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  get_indirect_mutex (int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  lck_mtx_interlock_lock_clear_flags (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  lck_mtx_unlock_finish_inline (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void lck_mtx_unlock_wakeup_tail (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ordered_load_mtx_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ordered_store_mtx_owner (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ordered_store_mtx_state_release (int /*<<< orphan*/ *,int) ; 

__attribute__((noinline))
void
lck_mtx_unlock_slow(
	lck_mtx_t	*lock)
{
	thread_t	thread;
	uint32_t	state, prev;
	boolean_t	indirect = FALSE;

	state = ordered_load_mtx_state(lock);

	/* Is this an indirect mutex? */
	if (__improbable(state == LCK_MTX_TAG_INDIRECT)) {
		indirect = get_indirect_mutex(&lock, &state);
	}

	thread = current_thread();

#if DEVELOPMENT | DEBUG
	thread_t owner = (thread_t)lock->lck_mtx_owner;
	if(__improbable(owner != thread))
		return lck_mtx_owner_check_panic(lock);
#endif

	/* check if it is held as a spinlock */
	if (__improbable((state & LCK_MTX_MLOCKED_MSK) == 0))
		goto unlock;

	lck_mtx_interlock_lock_clear_flags(lock, LCK_MTX_MLOCKED_MSK, &state);

unlock:
	/* preemption disabled, interlock held and mutex not held */

	/* clear owner */
	ordered_store_mtx_owner(lock, 0);
	/* keep original state in prev for later evaluation */
	prev = state;
	/* release interlock, promotion and clear spin flag */
	state &= (~(LCK_MTX_ILOCKED_MSK | LCK_MTX_SPIN_MSK | LCK_MTX_PROMOTED_MSK));
	if ((state & LCK_MTX_WAITERS_MSK))
		state -= LCK_MTX_WAITER;	/* decrement waiter count */
	ordered_store_mtx_state_release(lock, state);		/* since I own the interlock, I don't need an atomic update */

#if	MACH_LDEBUG
	/* perform lock statistics after drop to prevent delay */
	if (thread)
		thread->mutex_count--;		/* lock statistic */
#endif	/* MACH_LDEBUG */

	/* check if there are waiters to wake up or priority to drop */
	if ((prev & (LCK_MTX_PROMOTED_MSK | LCK_MTX_WAITERS_MSK)))
		return lck_mtx_unlock_wakeup_tail(lock, prev, indirect);

	/* re-enable preemption */
	lck_mtx_unlock_finish_inline(lock, FALSE);

	return;
}