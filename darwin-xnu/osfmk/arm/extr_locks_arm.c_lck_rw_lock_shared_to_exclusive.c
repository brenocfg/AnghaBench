#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ thread_t ;
struct TYPE_10__ {int /*<<< orphan*/  lck_rw_data; } ;
typedef  TYPE_1__ lck_rw_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int LCK_RW_INTERLOCK ; 
 int LCK_RW_SHARED_MASK ; 
 scalar_t__ LCK_RW_SHARED_READER ; 
 int LCK_RW_WANT_UPGRADE ; 
 int LCK_RW_W_WAITING ; 
 int /*<<< orphan*/  LOCKSTAT_RECORD (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LS_LCK_RW_LOCK_SHARED_TO_EXCL_UPGRADE ; 
 scalar_t__ THREAD_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assertf (int,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  atomic_exchange_abort () ; 
 int atomic_exchange_begin32 (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_exchange_complete32 (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_pause () ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  lck_rw_interlock_spin (TYPE_1__*) ; 
 int /*<<< orphan*/  lck_rw_lock_shared_to_exclusive_failure (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lck_rw_lock_shared_to_exclusive_success (TYPE_1__*) ; 
 int /*<<< orphan*/  memory_order_acquire_smp ; 
 int /*<<< orphan*/  ordered_load_rw (TYPE_1__*) ; 
 scalar_t__ ordered_load_rw_owner (TYPE_1__*) ; 
 int /*<<< orphan*/  ordered_store_rw_owner (TYPE_1__*,int /*<<< orphan*/ ) ; 

boolean_t
lck_rw_lock_shared_to_exclusive(lck_rw_t *lock)
{
	uint32_t	data, prev;

	for ( ; ; ) {
		data = atomic_exchange_begin32(&lock->lck_rw_data, &prev, memory_order_acquire_smp);
		if (data & LCK_RW_INTERLOCK) {
			atomic_exchange_abort();
			lck_rw_interlock_spin(lock);
			continue;
		}
		if (data & LCK_RW_WANT_UPGRADE) {
			data -= LCK_RW_SHARED_READER;
			if ((data & LCK_RW_SHARED_MASK) == 0)		/* we were the last reader */
				data &= ~(LCK_RW_W_WAITING);		/* so clear the wait indicator */
			if (atomic_exchange_complete32(&lock->lck_rw_data, prev, data, memory_order_acquire_smp))
				return lck_rw_lock_shared_to_exclusive_failure(lock, prev);
		} else {
			data |= LCK_RW_WANT_UPGRADE;		/* ask for WANT_UPGRADE */
			data -= LCK_RW_SHARED_READER;		/* and shed our read count */
			if (atomic_exchange_complete32(&lock->lck_rw_data, prev, data, memory_order_acquire_smp))
				break;
		}
		cpu_pause();
	}
										/* we now own the WANT_UPGRADE */
	if (data & LCK_RW_SHARED_MASK) 		/* check to see if all of the readers are drained */
		lck_rw_lock_shared_to_exclusive_success(lock);	/* if not, we need to go wait */
#if MACH_ASSERT
	thread_t owner = ordered_load_rw_owner(lock);
	assertf(owner == THREAD_NULL, "state=0x%x, owner=%p", ordered_load_rw(lock), owner);
#endif
	ordered_store_rw_owner(lock, current_thread());
#if	CONFIG_DTRACE
	LOCKSTAT_RECORD(LS_LCK_RW_LOCK_SHARED_TO_EXCL_UPGRADE, lock, 0);
#endif	/* CONFIG_DTRACE */
	return TRUE;
}