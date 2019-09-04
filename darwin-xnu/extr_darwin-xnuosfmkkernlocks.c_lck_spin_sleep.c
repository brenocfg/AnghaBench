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
typedef  scalar_t__ wait_result_t ;
typedef  int /*<<< orphan*/  wait_interrupt_t ;
typedef  int /*<<< orphan*/  lck_spin_t ;
typedef  int lck_sleep_action_t ;
typedef  int /*<<< orphan*/  event_t ;

/* Variables and functions */
 int LCK_SLEEP_MASK ; 
 int LCK_SLEEP_UNLOCK ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 scalar_t__ THREAD_WAITING ; 
 scalar_t__ assert_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 scalar_t__ thread_block (int /*<<< orphan*/ ) ; 

wait_result_t
lck_spin_sleep(
        lck_spin_t		*lck,
	lck_sleep_action_t	lck_sleep_action,
	event_t			event,
	wait_interrupt_t	interruptible)
{
	wait_result_t	res;
 
	if ((lck_sleep_action & ~LCK_SLEEP_MASK) != 0)
		panic("Invalid lock sleep action %x\n", lck_sleep_action);

	res = assert_wait(event, interruptible);
	if (res == THREAD_WAITING) {
		lck_spin_unlock(lck);
		res = thread_block(THREAD_CONTINUE_NULL);
		if (!(lck_sleep_action & LCK_SLEEP_UNLOCK))
			lck_spin_lock(lck);
	}
	else
	if (lck_sleep_action & LCK_SLEEP_UNLOCK)
		lck_spin_unlock(lck);

	return res;
}