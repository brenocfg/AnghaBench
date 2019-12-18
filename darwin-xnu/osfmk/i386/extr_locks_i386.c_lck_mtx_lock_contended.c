#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  TYPE_1__* thread_t ;
struct _lck_mtx_ext_ {int dummy; } ;
struct TYPE_15__ {scalar_t__ lck_mtx_owner; } ;
typedef  TYPE_2__ lck_mtx_t ;
typedef  int lck_mtx_spinwait_ret_type_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_14__ {scalar_t__ was_promoted_on_wakeup; int /*<<< orphan*/  mutex_count; } ;

/* Variables and functions */
 int LCK_MTX_ILOCKED_MSK ; 
 int LCK_MTX_MLOCKED_MSK ; 
#define  LCK_MTX_SPINWAIT_ACQUIRED 130 
#define  LCK_MTX_SPINWAIT_NO_SPIN 129 
#define  LCK_MTX_SPINWAIT_SPUN 128 
 int LCK_MTX_WAITERS_MSK ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  lck_mtx_interlock_lock (TYPE_2__*,int*) ; 
 void lck_mtx_lock_acquire_tail (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  lck_mtx_lock_finish_inline (TYPE_2__*,int,scalar_t__) ; 
 int lck_mtx_lock_spinwait_x86 (TYPE_2__*) ; 
 int /*<<< orphan*/  lck_mtx_lock_wait_x86 (TYPE_2__*) ; 
 int /*<<< orphan*/  lck_mtx_update_direct_wait (struct _lck_mtx_ext_*) ; 
 int /*<<< orphan*/  lck_mtx_update_miss (struct _lck_mtx_ext_*,scalar_t__*) ; 
 int /*<<< orphan*/  lck_mtx_update_wait (struct _lck_mtx_ext_*,scalar_t__*) ; 
 int ordered_load_mtx_state (TYPE_2__*) ; 
 int /*<<< orphan*/  ordered_store_mtx_owner (TYPE_2__*,uintptr_t) ; 
 int /*<<< orphan*/  ordered_store_mtx_state_release (TYPE_2__*,int) ; 
 int /*<<< orphan*/  panic (char*,int,TYPE_2__*) ; 

__attribute__((used)) __attribute__((noinline))
static void
lck_mtx_lock_contended(
	lck_mtx_t       *lock,
	boolean_t indirect,
	boolean_t *first_miss)
{
	lck_mtx_spinwait_ret_type_t ret;
	uint32_t state;
	thread_t thread;

try_again:

	if (indirect) {
		lck_mtx_update_miss((struct _lck_mtx_ext_*)lock, first_miss);
	}

	ret = lck_mtx_lock_spinwait_x86(lock);
	state = ordered_load_mtx_state(lock);
	switch (ret) {
	case LCK_MTX_SPINWAIT_NO_SPIN:
		/*
		 * owner not on core, lck_mtx_lock_spinwait_x86 didn't even
		 * try to spin.
		 */
		if (indirect) {
			lck_mtx_update_direct_wait((struct _lck_mtx_ext_*)lock);
		}

		/* just fall through case LCK_MTX_SPINWAIT_SPUN */
	case LCK_MTX_SPINWAIT_SPUN:
		/*
		 * mutex not acquired but lck_mtx_lock_spinwait_x86 tried to spin
		 * interlock not held
		 */
		lck_mtx_interlock_lock(lock, &state);
		assert(state & LCK_MTX_ILOCKED_MSK);

		if (state & LCK_MTX_MLOCKED_MSK) {
			if (indirect) {
				lck_mtx_update_wait((struct _lck_mtx_ext_*)lock, first_miss);
			}
			lck_mtx_lock_wait_x86(lock);
			/*
			 * interlock is not held here.
			 */
			goto try_again;
		} else {

			/* grab the mutex */
			state |= LCK_MTX_MLOCKED_MSK;
			ordered_store_mtx_state_release(lock, state);
			thread = current_thread();
			ordered_store_mtx_owner(lock, (uintptr_t)thread);
#if     MACH_LDEBUG
			if (thread) {
				thread->mutex_count++;
			}
#endif  /* MACH_LDEBUG */
		}

		break;
	case LCK_MTX_SPINWAIT_ACQUIRED:
		/*
		 * mutex has been acquired by lck_mtx_lock_spinwait_x86
		 * interlock is held and preemption disabled
		 * owner is set and mutex marked as locked
		 * statistics updated too
		 */
		break;
	default:
		panic("lck_mtx_lock_spinwait_x86 returned %d for mutex %p\n", ret, lock);
	}

	/*
	 * interlock is already acquired here
	 */

	/* mutex has been acquired */
	thread = (thread_t)lock->lck_mtx_owner;
	if (state & LCK_MTX_WAITERS_MSK || thread->was_promoted_on_wakeup) {
		return lck_mtx_lock_acquire_tail(lock, indirect);
	}

	/* release the interlock */
	lck_mtx_lock_finish_inline(lock, ordered_load_mtx_state(lock), indirect);
}