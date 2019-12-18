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
struct TYPE_7__ {int /*<<< orphan*/  lck_mtx_data; } ;
typedef  TYPE_1__ lck_mtx_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LCK_MTX_THREAD_TO_STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCKSTAT_RECORD (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LS_LCK_MTX_LOCK_ACQUIRE ; 
 scalar_t__ atomic_compare_exchange (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  lck_mtx_check_preemption (TYPE_1__*) ; 
 int /*<<< orphan*/  lck_mtx_lock_contended (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_verify (TYPE_1__*) ; 
 int /*<<< orphan*/  memory_order_acquire_smp ; 

void
lck_mtx_lock(lck_mtx_t *lock)
{
	thread_t	thread;

	lck_mtx_verify(lock);
	lck_mtx_check_preemption(lock);
	thread = current_thread();
	if (atomic_compare_exchange(&lock->lck_mtx_data, 0, LCK_MTX_THREAD_TO_STATE(thread),
					memory_order_acquire_smp, FALSE)) {
#if	CONFIG_DTRACE
		LOCKSTAT_RECORD(LS_LCK_MTX_LOCK_ACQUIRE, lock, 0);
#endif /* CONFIG_DTRACE */
		return;
	}
	lck_mtx_lock_contended(lock, thread, FALSE);
}