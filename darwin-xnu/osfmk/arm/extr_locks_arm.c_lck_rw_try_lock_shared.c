#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ thread_t ;
struct TYPE_9__ {int /*<<< orphan*/  lck_rw_data; } ;
typedef  TYPE_1__ lck_rw_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_10__ {int /*<<< orphan*/  rwlock_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_RW_SHARED ; 
 int /*<<< orphan*/  FALSE ; 
 int LCK_RW_INTERLOCK ; 
 scalar_t__ LCK_RW_SHARED_READER ; 
 int LCK_RW_WANT_EXCL ; 
 int LCK_RW_WANT_UPGRADE ; 
 int /*<<< orphan*/  LOCKSTAT_RECORD (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LS_LCK_RW_TRY_LOCK_SHARED_ACQUIRE ; 
 scalar_t__ THREAD_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assertf (int,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  atomic_exchange_abort () ; 
 int atomic_exchange_begin32 (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_exchange_complete32 (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_pause () ; 
 TYPE_7__* current_thread () ; 
 int /*<<< orphan*/  lck_rw_interlock_spin (TYPE_1__*) ; 
 int /*<<< orphan*/  memory_order_acquire_smp ; 
 int /*<<< orphan*/  ordered_load_rw (TYPE_1__*) ; 
 scalar_t__ ordered_load_rw_owner (TYPE_1__*) ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*,int) ; 

boolean_t lck_rw_try_lock_shared(lck_rw_t *lock)
{
	uint32_t	data, prev;

	for ( ; ; ) {
		data = atomic_exchange_begin32(&lock->lck_rw_data, &prev, memory_order_acquire_smp);
		if (data & LCK_RW_INTERLOCK) {
#if __SMP__
			atomic_exchange_abort();
			lck_rw_interlock_spin(lock);
			continue;
#else
			panic("lck_rw_try_lock_shared(): Interlock locked (%p): %x", lock, data);
#endif
		}
		if (data & (LCK_RW_WANT_EXCL | LCK_RW_WANT_UPGRADE)) {
			atomic_exchange_abort();
			return FALSE;						/* lock is busy */
		}
		data += LCK_RW_SHARED_READER;			/* Increment reader refcount */
		if (atomic_exchange_complete32(&lock->lck_rw_data, prev, data, memory_order_acquire_smp))
			break;
		cpu_pause();
	}
#if MACH_ASSERT
	thread_t owner = ordered_load_rw_owner(lock);
	assertf(owner == THREAD_NULL, "state=0x%x, owner=%p", ordered_load_rw(lock), owner);
#endif
	current_thread()->rwlock_count++;
#if	CONFIG_DTRACE
	LOCKSTAT_RECORD(LS_LCK_RW_TRY_LOCK_SHARED_ACQUIRE, lock, DTRACE_RW_SHARED);
#endif	/* CONFIG_DTRACE */
	return TRUE;
}