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
struct TYPE_3__ {int /*<<< orphan*/  lck_mtx_state; } ;
typedef  TYPE_1__ lck_mtx_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int LCK_MTX_ILOCKED_MSK ; 
 scalar_t__ atomic_compare_exchange32 (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_preemption () ; 
 int /*<<< orphan*/  enable_preemption () ; 
 int /*<<< orphan*/  memory_order_acquire_smp ; 

__attribute__((used)) static inline int
lck_mtx_interlock_try_lock_set_flags(
	lck_mtx_t *mutex,
	uint32_t or_flags,
	uint32_t *new_state)
{
	uint32_t state, prev;
	state = *new_state;

	/* have to wait for interlock to clear */
	if (state & (LCK_MTX_ILOCKED_MSK | or_flags)) {
		return 0;
	}
	prev = state;					/* prev contains snapshot for exchange */
	state |= LCK_MTX_ILOCKED_MSK | or_flags;	/* pick up interlock */
	disable_preemption();
	if (atomic_compare_exchange32(&mutex->lck_mtx_state, prev, state, memory_order_acquire_smp, FALSE)) {
			*new_state = state;
			return 1;
	}

	enable_preemption();
	return 0;
}