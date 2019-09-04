#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ boolean_t ;
struct TYPE_2__ {scalar_t__ kds_inuse_count; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 TYPE_1__ kd_ctrl_page ; 
 scalar_t__ kds_waiter ; 
 int /*<<< orphan*/  kdw_spin_lock ; 
 scalar_t__ lck_spin_try_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_spin_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ ml_set_interrupts_enabled (scalar_t__) ; 
 scalar_t__ n_storage_threshold ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

__attribute__((used)) static void
kdbg_wakeup(void)
{
	boolean_t need_kds_wakeup = FALSE;

	/*
	 * Try to take the lock here to synchronize with the waiter entering
	 * the blocked state.  Use the try mode to prevent deadlocks caused by
	 * re-entering this routine due to various trace points triggered in the
	 * lck_spin_sleep_xxxx routines used to actually enter one of our 2 wait
	 * conditions.  No problem if we fail, there will be lots of additional
	 * events coming in that will eventually succeed in grabbing this lock.
	 */
	boolean_t s = ml_set_interrupts_enabled(FALSE);

	if (lck_spin_try_lock(kdw_spin_lock)) {
		if (kds_waiter &&
		    (kd_ctrl_page.kds_inuse_count >= n_storage_threshold))
		{
			kds_waiter = 0;
			need_kds_wakeup = TRUE;
		}
		lck_spin_unlock(kdw_spin_lock);
	}

	ml_set_interrupts_enabled(s);

	if (need_kds_wakeup == TRUE) {
		wakeup(&kds_waiter);
	}
}