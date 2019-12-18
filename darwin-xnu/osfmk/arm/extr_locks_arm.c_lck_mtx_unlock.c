#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ thread_t ;
struct TYPE_7__ {int /*<<< orphan*/  lck_mtx_data; } ;
typedef  TYPE_1__ lck_mtx_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 uintptr_t LCK_ILOCK ; 
 scalar_t__ LCK_MTX_SPIN_TAG ; 
 scalar_t__ LCK_MTX_STATE_TO_THREAD (uintptr_t) ; 
 int /*<<< orphan*/  LCK_MTX_THREAD_TO_STATE (scalar_t__) ; 
 int /*<<< orphan*/  LOCKSTAT_RECORD (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LS_LCK_MTX_UNLOCK_RELEASE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ atomic_compare_exchange (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ current_thread () ; 
 int /*<<< orphan*/  lck_mtx_unlock_contended (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_verify (TYPE_1__*) ; 
 int /*<<< orphan*/  memory_order_release_smp ; 
 uintptr_t ordered_load_mtx (TYPE_1__*) ; 

void
lck_mtx_unlock(lck_mtx_t *lock)
{
	thread_t	thread = current_thread();
	uintptr_t	state;
	boolean_t	ilk_held = FALSE;

	lck_mtx_verify(lock);

	state = ordered_load_mtx(lock);
	if (state & LCK_ILOCK) {
		if(LCK_MTX_STATE_TO_THREAD(state) == (thread_t)LCK_MTX_SPIN_TAG)
			ilk_held = TRUE;	// Interlock is held by (presumably) this thread
		goto slow_case;
	}
	// Locked as a mutex
	if (atomic_compare_exchange(&lock->lck_mtx_data, LCK_MTX_THREAD_TO_STATE(thread), 0,
					memory_order_release_smp, FALSE)) {
#if	CONFIG_DTRACE
		LOCKSTAT_RECORD(LS_LCK_MTX_UNLOCK_RELEASE, lock, 0);
#endif /* CONFIG_DTRACE */
		return;
	}
slow_case:
	lck_mtx_unlock_contended(lock, thread, ilk_held);
}