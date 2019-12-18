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
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  ap_poll_timer ; 
 int /*<<< orphan*/  ap_poll_timer_lock ; 
 scalar_t__ ap_suspend_flag ; 
 int /*<<< orphan*/  hrtimer_expires_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_forward_now (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hrtimer_is_queued (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_restart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_timeout ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __ap_schedule_poll_timer(void)
{
	ktime_t hr_time;

	spin_lock_bh(&ap_poll_timer_lock);
	if (hrtimer_is_queued(&ap_poll_timer) || ap_suspend_flag)
		goto out;
	if (ktime_to_ns(hrtimer_expires_remaining(&ap_poll_timer)) <= 0) {
		hr_time = ktime_set(0, poll_timeout);
		hrtimer_forward_now(&ap_poll_timer, hr_time);
		hrtimer_restart(&ap_poll_timer);
	}
out:
	spin_unlock_bh(&ap_poll_timer_lock);
}