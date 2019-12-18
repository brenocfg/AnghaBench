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
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ lck_rw_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int LCK_RW_INTERLOCK ; 
 int LCK_RW_PRIV_EXCL ; 
 int LCK_RW_SHARED_MASK ; 
 scalar_t__ LCK_RW_SHARED_READER ; 
 int LCK_RW_WANT_UPGRADE ; 
 int LCK_RW_WANT_WRITE ; 
 int /*<<< orphan*/  atomic_exchange_abort () ; 
 int atomic_exchange_begin32 (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_exchange_complete32 (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_interlock_spin (TYPE_1__*) ; 
 int /*<<< orphan*/  memory_order_acquire_smp ; 

__attribute__((used)) static boolean_t
lck_rw_grab_shared(lck_rw_t *lock)
{
	uint32_t	data, prev;

	for ( ; ; ) {
		data = atomic_exchange_begin32(&lock->data, &prev, memory_order_acquire_smp);
		if ((data & LCK_RW_INTERLOCK) == 0)
			break;
		atomic_exchange_abort();
		lck_rw_interlock_spin(lock);
	}
	if (data & (LCK_RW_WANT_WRITE | LCK_RW_WANT_UPGRADE)) {
		if (((data & LCK_RW_SHARED_MASK) == 0) || (data & LCK_RW_PRIV_EXCL)) {
			atomic_exchange_abort();
			return FALSE;
		}
	}
	data += LCK_RW_SHARED_READER;
	return atomic_exchange_complete32(&lock->data, prev, data, memory_order_acquire_smp);
}