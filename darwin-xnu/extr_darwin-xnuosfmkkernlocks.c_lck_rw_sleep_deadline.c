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
typedef  scalar_t__ wait_result_t ;
typedef  int /*<<< orphan*/  wait_interrupt_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_1__* thread_t ;
typedef  int lck_sleep_action_t ;
typedef  int /*<<< orphan*/  lck_rw_type_t ;
typedef  int /*<<< orphan*/  lck_rw_t ;
typedef  int /*<<< orphan*/  event_t ;
struct TYPE_4__ {int sched_flags; int /*<<< orphan*/  rwlock_count; } ;

/* Variables and functions */
 int LCK_SLEEP_EXCLUSIVE ; 
 int LCK_SLEEP_MASK ; 
 int LCK_SLEEP_PROMOTED_PRI ; 
 int LCK_SLEEP_SHARED ; 
 int LCK_SLEEP_UNLOCK ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 scalar_t__ THREAD_WAITING ; 
 int TH_SFLAG_RW_PROMOTED ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ assert_wait_deadline (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  lck_rw_clear_promotion (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 scalar_t__ thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unslide_for_kdebug (int /*<<< orphan*/ ) ; 

wait_result_t
lck_rw_sleep_deadline(
	lck_rw_t		*lck,
	lck_sleep_action_t	lck_sleep_action,
	event_t			event,
	wait_interrupt_t	interruptible,
	uint64_t		deadline)
{
	wait_result_t   res;
	lck_rw_type_t	lck_rw_type;
	thread_t		thread = current_thread();

	if ((lck_sleep_action & ~LCK_SLEEP_MASK) != 0)
		panic("Invalid lock sleep action %x\n", lck_sleep_action);

	if (lck_sleep_action & LCK_SLEEP_PROMOTED_PRI) {
		thread->rwlock_count++;
	}

	res = assert_wait_deadline(event, interruptible, deadline);
	if (res == THREAD_WAITING) {
		lck_rw_type = lck_rw_done(lck);
		res = thread_block(THREAD_CONTINUE_NULL);
		if (!(lck_sleep_action & LCK_SLEEP_UNLOCK)) {
			if (!(lck_sleep_action & (LCK_SLEEP_SHARED|LCK_SLEEP_EXCLUSIVE)))
				lck_rw_lock(lck, lck_rw_type);
			else if (lck_sleep_action & LCK_SLEEP_EXCLUSIVE)
				lck_rw_lock_exclusive(lck);
			else
				lck_rw_lock_shared(lck);
		}
	}
	else
	if (lck_sleep_action & LCK_SLEEP_UNLOCK)
		(void)lck_rw_done(lck);

	if (lck_sleep_action & LCK_SLEEP_PROMOTED_PRI) {
		if ((thread->rwlock_count-- == 1 /* field now 0 */) && (thread->sched_flags & TH_SFLAG_RW_PROMOTED)) {
			/* sched_flags checked without lock, but will be rechecked while clearing */

			/* Only if the caller wanted the lck_rw_t returned unlocked should we drop to 0 */
			assert(lck_sleep_action & LCK_SLEEP_UNLOCK);

			lck_rw_clear_promotion(thread, unslide_for_kdebug(event));
		}
	}

	return res;
}