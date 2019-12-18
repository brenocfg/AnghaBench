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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LOCKSTAT_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  LS_LCK_SPIN_LOCK_ACQUIRE ; 
 scalar_t__ __improbable (int) ; 
 int /*<<< orphan*/  atomic_test_and_set32 (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int hw_lock_bit_to_contended (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  memory_order_acquire ; 
 int ordered_load_bit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ordered_store_bit (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline unsigned int
hw_lock_bit_to_internal(hw_lock_bit_t *lock, unsigned int bit, uint32_t timeout)
{
	unsigned int success = 0;
	uint32_t	mask = (1 << bit);
#if	!__SMP__
	uint32_t	state;
#endif

#if	__SMP__
	if (__improbable(!atomic_test_and_set32(lock, mask, mask, memory_order_acquire, FALSE)))
		success = hw_lock_bit_to_contended(lock, mask, timeout);
	else
		success = 1;
#else	// __SMP__
	(void)timeout;
	state = ordered_load_bit(lock);
	if (!(mask & state)) {
		ordered_store_bit(lock, state | mask);
		success = 1;
	}
#endif	// __SMP__

#if CONFIG_DTRACE
	if (success)
		LOCKSTAT_RECORD(LS_LCK_SPIN_LOCK_ACQUIRE, lock, bit);
#endif

	return success;
}