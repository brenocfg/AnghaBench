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
typedef  scalar_t__ thread_t ;
typedef  int /*<<< orphan*/  lck_mtx_t ;

/* Variables and functions */
 uintptr_t ARM_LCK_WAITERS ; 
 uintptr_t LCK_ILOCK ; 
 scalar_t__ LCK_MTX_SPIN_TAG ; 
 scalar_t__ LCK_MTX_STATE_TO_THREAD (uintptr_t) ; 
 uintptr_t LCK_MTX_THREAD_MASK ; 
 uintptr_t LCK_MTX_THREAD_TO_STATE (scalar_t__) ; 
 scalar_t__ current_thread () ; 
 int /*<<< orphan*/  enable_preemption () ; 
 int /*<<< orphan*/  interlock_unlock (int /*<<< orphan*/ *) ; 
 int lck_mtx_lock_acquire (int /*<<< orphan*/ *) ; 
 uintptr_t ordered_load_mtx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ordered_store_mtx (int /*<<< orphan*/ *,uintptr_t) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ *) ; 

void
lck_mtx_convert_spin(lck_mtx_t *lock)
{
	thread_t	thread = current_thread();
	uintptr_t	state;
	int			waiters;

	state = ordered_load_mtx(lock);
	if (LCK_MTX_STATE_TO_THREAD(state) == thread)
		return;		// Already owned as mutex, return
	if ((state & LCK_ILOCK) == 0 || (LCK_MTX_STATE_TO_THREAD(state) != (thread_t)LCK_MTX_SPIN_TAG))
		panic("lck_mtx_convert_spin: Not held as spinlock (%p)", lock);
	state &= ~(LCK_MTX_THREAD_MASK);		// Clear the spin tag
	ordered_store_mtx(lock, state);
	waiters = lck_mtx_lock_acquire(lock);	// Acquire to manage priority boosts
	state = LCK_MTX_THREAD_TO_STATE(thread);
	if (waiters != 0)
		state |= ARM_LCK_WAITERS;
#if __SMP__
	state |= LCK_ILOCK;
	ordered_store_mtx(lock, state);			// Set ownership
	interlock_unlock(lock);					// Release interlock, enable preemption
#else
	ordered_store_mtx(lock, state);			// Set ownership
	enable_preemption();
#endif
}