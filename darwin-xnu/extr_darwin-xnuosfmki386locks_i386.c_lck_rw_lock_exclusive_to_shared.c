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
typedef  int uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ lck_rw_t ;

/* Variables and functions */
 int LCK_RW_INTERLOCK ; 
 int LCK_RW_PRIV_EXCL ; 
 scalar_t__ LCK_RW_SHARED_READER ; 
 int LCK_RW_WANT_EXCL ; 
 int LCK_RW_WANT_UPGRADE ; 
 int LCK_RW_W_WAITING ; 
 int /*<<< orphan*/  atomic_exchange_abort () ; 
 int atomic_exchange_begin32 (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_exchange_complete32 (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_pause () ; 
 int /*<<< orphan*/  lck_rw_interlock_spin (TYPE_1__*) ; 
 void lck_rw_lock_exclusive_to_shared_gen (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memory_order_release_smp ; 

void lck_rw_lock_exclusive_to_shared(lck_rw_t *lock)
{
	uint32_t	data, prev;

	for ( ; ; ) {
		data = atomic_exchange_begin32(&lock->data, &prev, memory_order_release_smp);
		if (data & LCK_RW_INTERLOCK) {
			atomic_exchange_abort();
			lck_rw_interlock_spin(lock);	/* wait for interlock to clear */
			continue;
		}
		data += LCK_RW_SHARED_READER;
		if (data & LCK_RW_WANT_UPGRADE)
			data &= ~(LCK_RW_WANT_UPGRADE);
		else
			data &= ~(LCK_RW_WANT_EXCL);
		if (!((prev & LCK_RW_W_WAITING) && (prev & LCK_RW_PRIV_EXCL)))
			data &= ~(LCK_RW_W_WAITING);
		if (atomic_exchange_complete32(&lock->data, prev, data, memory_order_release_smp))
			break;
		cpu_pause();
	}
	return lck_rw_lock_exclusive_to_shared_gen(lock, prev);
}