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
typedef  unsigned int boolean_t ;

/* Variables and functions */
 unsigned int FALSE ; 
 int /*<<< orphan*/  LOCKSTAT_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  LS_LCK_SPIN_LOCK_ACQUIRE ; 
 unsigned int TRUE ; 
 int /*<<< orphan*/  _disable_preemption () ; 
 int /*<<< orphan*/  _enable_preemption () ; 
 unsigned int atomic_test_and_set32 (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memory_order_acquire ; 
 int ordered_load_bit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ordered_store_bit (int /*<<< orphan*/ *,int) ; 

unsigned int
hw_lock_bit_try(hw_lock_bit_t *lock, unsigned int bit)
{
	uint32_t	mask = (1 << bit);
#if	!__SMP__
	uint32_t	state;
#endif
	boolean_t	success = FALSE;

	_disable_preemption();
#if	__SMP__
	// TODO: consider weak (non-looping) atomic test-and-set
	success = atomic_test_and_set32(lock, mask, mask, memory_order_acquire, FALSE);
#else
	state = ordered_load_bit(lock);
	if (!(mask & state)) {
		ordered_store_bit(lock, state | mask);
		success = TRUE;
	}
#endif	// __SMP__
	if (!success)
		_enable_preemption();

#if CONFIG_DTRACE
	if (success)
		LOCKSTAT_RECORD(LS_LCK_SPIN_LOCK_ACQUIRE, lock, bit);
#endif

	return success;
}