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
typedef  int uint32_t ;
typedef  scalar_t__ thread_t ;
struct TYPE_8__ {scalar_t__ lck_mtx_owner; } ;
typedef  TYPE_1__ lck_mtx_t ;

/* Variables and functions */
 int LCK_MTX_ILOCKED_MSK ; 
 int LCK_MTX_MLOCKED_MSK ; 
 int LCK_MTX_SPIN_MSK ; 
 int LCK_MTX_TAG_INDIRECT ; 
 int LCK_MTX_WAITERS_MSK ; 
 scalar_t__ __improbable (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertf (int,char*,TYPE_1__*,scalar_t__,scalar_t__) ; 
 scalar_t__ current_thread () ; 
 int /*<<< orphan*/  get_indirect_mutex (TYPE_1__**,int*) ; 
 scalar_t__ get_preemption_level () ; 
 void lck_mtx_convert_spin_acquire_tail (TYPE_1__*) ; 
 int /*<<< orphan*/  lck_mtx_convert_spin_finish_inline (TYPE_1__*,int) ; 
 int ordered_load_mtx_state (TYPE_1__*) ; 

__attribute__((noinline))
void
lck_mtx_convert_spin(
	lck_mtx_t 	*lock)
{
	uint32_t state;

	state = ordered_load_mtx_state(lock);

	/* Is this an indirect mutex? */
	if (__improbable(state == LCK_MTX_TAG_INDIRECT)) {
		/* If so, take indirection */
		get_indirect_mutex(&lock, &state);
	}

	assertf((thread_t)lock->lck_mtx_owner == current_thread(), "lock %p not owned by thread %p (current owner %p)", lock, current_thread(), (thread_t)lock->lck_mtx_owner );

	if (__improbable(state & LCK_MTX_MLOCKED_MSK)) {
		/* already owned as a mutex, just return */
		return;
	}

	assert(get_preemption_level() > 0);
	assert(state & LCK_MTX_ILOCKED_MSK);
	assert(state & LCK_MTX_SPIN_MSK);

	/*
	 * Check if there are waiters to
	 * inherit their priority.
	 */
	if (__improbable(state & LCK_MTX_WAITERS_MSK)) {
		return lck_mtx_convert_spin_acquire_tail(lock);
	}

	lck_mtx_convert_spin_finish_inline(lock, ordered_load_mtx_state(lock));

	return;
}