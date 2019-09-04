#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  hw_lock_bit_t ;

/* Variables and functions */
 int ordered_load_bit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ordered_store_bit (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void
hw_unlock_bit_internal(hw_lock_bit_t *lock, unsigned int bit)
{
	uint32_t	mask = (1 << bit);
#if	!__SMP__
	uint32_t	state;
#endif

#if	__SMP__
	__c11_atomic_fetch_and((_Atomic uint32_t *)lock, ~mask, memory_order_release);
	set_event();
#else	// __SMP__
	state = ordered_load_bit(lock);
	ordered_store_bit(lock, state & ~mask);
#endif	// __SMP__
#if CONFIG_DTRACE
	LOCKSTAT_RECORD(LS_LCK_SPIN_UNLOCK_RELEASE, lock, bit);
#endif
}