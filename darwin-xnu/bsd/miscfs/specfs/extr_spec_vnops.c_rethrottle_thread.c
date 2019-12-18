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
typedef  TYPE_1__* uthread_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {int uu_is_throttled; int uu_was_rethrottled; int uu_on_throttlelist; int /*<<< orphan*/  uu_rethrottle_lock; int /*<<< orphan*/  uu_thread; int /*<<< orphan*/ * uu_throttle_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FSRW ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FSDBG_CODE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rethrottle_wakeups ; 
 int /*<<< orphan*/  thread_tid (int /*<<< orphan*/ ) ; 
 int throttle_get_thread_throttle_level (TYPE_1__*) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

void
rethrottle_thread(uthread_t ut)
{
	/*
	 * If uthread doesn't have throttle state, then there's no chance
	 * of it needing a rethrottle.
	 */
	if (ut->uu_throttle_info == NULL)
		return;

	boolean_t s = ml_set_interrupts_enabled(FALSE);
	lck_spin_lock(&ut->uu_rethrottle_lock);

	if (!ut->uu_is_throttled)
		ut->uu_was_rethrottled = true;
	else {
		int my_new_level = throttle_get_thread_throttle_level(ut);

		if (my_new_level != ut->uu_on_throttlelist) {
			/*
			 * ut is currently blocked (as indicated by
			 * ut->uu_is_throttled == true)
			 * and we're changing it's throttle level, so
			 * we need to wake it up.
			 */
			ut->uu_is_throttled = false;
			wakeup(&ut->uu_on_throttlelist);

			rethrottle_wakeups++;
			KERNEL_DEBUG_CONSTANT((FSDBG_CODE(DBG_FSRW, 102)), thread_tid(ut->uu_thread), ut->uu_on_throttlelist, my_new_level, 0, 0);
		}
	}
	lck_spin_unlock(&ut->uu_rethrottle_lock);
	ml_set_interrupts_enabled(s);
}