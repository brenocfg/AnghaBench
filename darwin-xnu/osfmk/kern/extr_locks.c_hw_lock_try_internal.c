#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_t ;
typedef  TYPE_1__* hw_lock_t ;
struct TYPE_5__ {int lock_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int LCK_MTX_THREAD_TO_STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCKSTAT_RECORD (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LS_LCK_SPIN_LOCK_ACQUIRE ; 
 int PLATFORM_LCK_ILOCK ; 
 int atomic_compare_exchange (int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_order_acquire_smp ; 
 scalar_t__ ordered_load_hw (TYPE_1__*) ; 

__attribute__((used)) static inline unsigned int
hw_lock_try_internal(hw_lock_t lock, thread_t thread)
{
	int		success = 0;

#if	__SMP__
#if	LOCK_PRETEST
	if (ordered_load_hw(lock))
		goto failed;
#endif	// LOCK_PRETEST
	success = atomic_compare_exchange(&lock->lock_data, 0, LCK_MTX_THREAD_TO_STATE(thread) | PLATFORM_LCK_ILOCK,
					memory_order_acquire_smp, FALSE);
#else
	if (lock->lock_data == 0) {
		lock->lock_data = LCK_MTX_THREAD_TO_STATE(thread) | PLATFORM_LCK_ILOCK;
		success = 1;
	}
#endif	// __SMP__

#if	LOCK_PRETEST
failed:
#endif	// LOCK_PRETEST
#if CONFIG_DTRACE
	if (success)
		LOCKSTAT_RECORD(LS_LCK_SPIN_LOCK_ACQUIRE, lock, 0);
#endif
	return success;
}