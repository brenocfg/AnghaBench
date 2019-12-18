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
typedef  int uint64_t ;
typedef  int boolean_t ;
struct TYPE_2__ {scalar_t__ kds_inuse_count; } ;

/* Variables and functions */
 int FALSE ; 
 int NSEC_PER_MSEC ; 
 int /*<<< orphan*/  THREAD_ABORTSAFE ; 
 int THREAD_AWAKENED ; 
 int /*<<< orphan*/  clock_absolutetime_interval_to_deadline (int,int*) ; 
 TYPE_1__ kd_ctrl_page ; 
 int kds_waiter ; 
 int /*<<< orphan*/  kdw_spin_lock ; 
 int /*<<< orphan*/  ktrace_assert_lock_held () ; 
 int /*<<< orphan*/  ktrace_lock () ; 
 int /*<<< orphan*/  ktrace_unlock () ; 
 int /*<<< orphan*/  lck_spin_lock (int /*<<< orphan*/ ) ; 
 int lck_spin_sleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int lck_spin_sleep_deadline (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lck_spin_unlock (int /*<<< orphan*/ ) ; 
 int ml_set_interrupts_enabled (int) ; 
 scalar_t__ n_storage_threshold ; 
 int /*<<< orphan*/  nanoseconds_to_absolutetime (int,int*) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static boolean_t
kdbg_wait(uint64_t timeout_ms, boolean_t locked_wait)
{
	int wait_result = THREAD_AWAKENED;
	uint64_t abstime = 0;

	ktrace_assert_lock_held();

	if (timeout_ms != 0) {
		uint64_t ns = timeout_ms * NSEC_PER_MSEC;
		nanoseconds_to_absolutetime(ns,  &abstime);
		clock_absolutetime_interval_to_deadline(abstime, &abstime);
	}

	boolean_t s = ml_set_interrupts_enabled(FALSE);
	if (!s) {
		panic("kdbg_wait() called with interrupts disabled");
	}
	lck_spin_lock(kdw_spin_lock);

	if (!locked_wait) {
		/* drop the mutex to allow others to access trace */
		ktrace_unlock();
	}

	while (wait_result == THREAD_AWAKENED &&
	       kd_ctrl_page.kds_inuse_count < n_storage_threshold)
	{
		kds_waiter = 1;

		if (abstime) {
			wait_result = lck_spin_sleep_deadline(kdw_spin_lock, 0, &kds_waiter, THREAD_ABORTSAFE, abstime);
		} else {
			wait_result = lck_spin_sleep(kdw_spin_lock, 0, &kds_waiter, THREAD_ABORTSAFE);
		}

		kds_waiter = 0;
	}

	/* check the count under the spinlock */
	boolean_t threshold_exceeded = (kd_ctrl_page.kds_inuse_count >= n_storage_threshold);

	lck_spin_unlock(kdw_spin_lock);
	ml_set_interrupts_enabled(s);

	if (!locked_wait) {
		/* pick the mutex back up again */
		ktrace_lock();
	}

	/* write out whether we've exceeded the threshold */
	return threshold_exceeded;
}