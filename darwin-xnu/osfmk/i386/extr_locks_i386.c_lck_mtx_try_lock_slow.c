#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  TYPE_1__* thread_t ;
struct _lck_mtx_ext_ {int dummy; } ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  mutex_count; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int LCK_MTX_ILOCKED_MSK ; 
 int LCK_MTX_MLOCKED_MSK ; 
 int LCK_MTX_TAG_DESTROYED ; 
 int LCK_MTX_TAG_INDIRECT ; 
 int LCK_MTX_WAITERS_MSK ; 
 scalar_t__ TRUE ; 
 scalar_t__ __improbable (int) ; 
 TYPE_1__* current_thread () ; 
 scalar_t__ get_indirect_mutex (int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  lck_mtx_interlock_try_lock_set_flags (int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ lck_mtx_try_destroyed (int /*<<< orphan*/ *) ; 
 scalar_t__ lck_mtx_try_lock_acquire_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_try_lock_finish_inline (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lck_mtx_try_lock_wait_interlock_to_clear (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  lck_mtx_update_miss (struct _lck_mtx_ext_*,int*) ; 
 int /*<<< orphan*/  lck_mtx_update_util (struct _lck_mtx_ext_*) ; 
 int ordered_load_mtx_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ordered_store_mtx_owner (int /*<<< orphan*/ *,uintptr_t) ; 

__attribute__((noinline))
boolean_t
lck_mtx_try_lock_slow(
	lck_mtx_t       *lock)
{
	boolean_t       indirect = FALSE;
	uint32_t        state;
	int             first_miss = 0;

	state = ordered_load_mtx_state(lock);

	/* is the interlock or mutex held */
	if (__improbable(state & ((LCK_MTX_ILOCKED_MSK | LCK_MTX_MLOCKED_MSK)))) {
		/*
		 * Note: both LCK_MTX_TAG_DESTROYED and LCK_MTX_TAG_INDIRECT
		 * have LCK_MTX_ILOCKED_MSK and LCK_MTX_MLOCKED_MSK
		 * set in state (state == lck_mtx_tag)
		 */

		/* is the mutex already held and not indirect */
		if (__improbable(!(state & LCK_MTX_ILOCKED_MSK))){
			return FALSE;
		}

		/* check to see if it is marked destroyed */
		if (__improbable(state == LCK_MTX_TAG_DESTROYED)) {
			return lck_mtx_try_destroyed(lock);
		}

		/* Is this an indirect mutex? */
		if (__improbable(state == LCK_MTX_TAG_INDIRECT)) {
			indirect = get_indirect_mutex(&lock, &state);

			first_miss = 0;
			lck_mtx_update_util((struct _lck_mtx_ext_*)lock);
		}

		if (!lck_mtx_try_lock_wait_interlock_to_clear(lock, &state)) {
			if (indirect)
				lck_mtx_update_miss((struct _lck_mtx_ext_*)lock, &first_miss);
			return FALSE;
		}
	}

	/* no - can't be INDIRECT, DESTROYED or locked */
	while (__improbable(!lck_mtx_interlock_try_lock_set_flags(lock, LCK_MTX_MLOCKED_MSK, &state))) {
		if (!lck_mtx_try_lock_wait_interlock_to_clear(lock, &state)) {
			if (indirect)
				lck_mtx_update_miss((struct _lck_mtx_ext_*)lock, &first_miss);
			return FALSE;
		}
	}

	/* lock and interlock acquired */

	thread_t thread = current_thread();
	/* record owner of mutex */
	ordered_store_mtx_owner(lock, (uintptr_t)thread);

#if MACH_LDEBUG
	if (thread) {
		thread->mutex_count++;		/* lock statistic */
	}
#endif
	/*
	 * Check if there are waiters to
	 * inherit their priority.
	 */
	if (__improbable(state & LCK_MTX_WAITERS_MSK)) {
		return lck_mtx_try_lock_acquire_tail(lock);
	}

	/* release the interlock */
	lck_mtx_try_lock_finish_inline(lock, ordered_load_mtx_state(lock));

	return TRUE;

}