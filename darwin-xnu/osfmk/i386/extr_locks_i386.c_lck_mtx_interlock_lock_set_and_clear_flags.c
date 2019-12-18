#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  lck_mtx_state; } ;
typedef  TYPE_1__ lck_mtx_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int LCK_MTX_ILOCKED_MSK ; 
 scalar_t__ __improbable (int) ; 
 scalar_t__ atomic_compare_exchange32 (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_pause () ; 
 int /*<<< orphan*/  disable_preemption () ; 
 int /*<<< orphan*/  enable_preemption () ; 
 int /*<<< orphan*/  memory_order_acquire_smp ; 
 int ordered_load_mtx_state (TYPE_1__*) ; 

__attribute__((used)) static inline void
lck_mtx_interlock_lock_set_and_clear_flags(
	lck_mtx_t *mutex,
	uint32_t xor_flags,
	uint32_t and_flags,
	uint32_t *new_state)
{
	uint32_t state, prev;
	state = *new_state;

	for ( ; ; ) {
		/* have to wait for interlock to clear */
		while (__improbable(state & (LCK_MTX_ILOCKED_MSK | xor_flags))) {
			cpu_pause();
			state = ordered_load_mtx_state(mutex);
		}
		prev = state;                                   /* prev contains snapshot for exchange */
		state |= LCK_MTX_ILOCKED_MSK | xor_flags;       /* pick up interlock */
		state &= ~and_flags;                    	/* clear flags */

		disable_preemption();
		if (atomic_compare_exchange32(&mutex->lck_mtx_state, prev, state, memory_order_acquire_smp, FALSE))
			break;
		enable_preemption();
		cpu_pause();
		state = ordered_load_mtx_state(mutex);
	}
	*new_state = state;
	return;
}