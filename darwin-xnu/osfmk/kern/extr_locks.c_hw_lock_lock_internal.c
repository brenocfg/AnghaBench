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
typedef  int /*<<< orphan*/  thread_t ;
typedef  TYPE_1__* hw_lock_t ;
struct TYPE_7__ {uintptr_t lock_data; } ;

/* Variables and functions */
 uintptr_t LCK_MTX_THREAD_TO_STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCKSTAT_RECORD (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LS_LCK_SPIN_LOCK_ACQUIRE ; 
 uintptr_t PLATFORM_LCK_ILOCK ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ atomic_compare_exchange (uintptr_t*,int /*<<< orphan*/ ,uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_lock_lock_contended (TYPE_1__*,uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_order_acquire_smp ; 
 scalar_t__ ordered_load_hw (TYPE_1__*) ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  spinlock_timeout_panic ; 

__attribute__((used)) static inline void
hw_lock_lock_internal(hw_lock_t lock, thread_t thread)
{
	uintptr_t	state;

	state = LCK_MTX_THREAD_TO_STATE(thread) | PLATFORM_LCK_ILOCK;
#if	__SMP__

#if	LOCK_PRETEST
	if (ordered_load_hw(lock))
		goto contended;
#endif	// LOCK_PRETEST
	if (atomic_compare_exchange(&lock->lock_data, 0, state,
					memory_order_acquire_smp, TRUE)) {
		goto end;
	}
#if	LOCK_PRETEST
contended:
#endif	// LOCK_PRETEST
	hw_lock_lock_contended(lock, state, 0, spinlock_timeout_panic);
end:
#else	// __SMP__
	if (lock->lock_data)
		panic("Spinlock held %p", lock);
	lock->lock_data = state;
#endif	// __SMP__
#if CONFIG_DTRACE
	LOCKSTAT_RECORD(LS_LCK_SPIN_LOCK_ACQUIRE, lock, 0);
#endif
	return;
}