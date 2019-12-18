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
struct hrtimer {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_ABS_PINNED ; 
 int /*<<< orphan*/  __hrtimer_start_range_ns (struct hrtimer*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hrtimer_active (struct hrtimer*) ; 
 int /*<<< orphan*/  hrtimer_cb_get_time (struct hrtimer*) ; 
 int /*<<< orphan*/  hrtimer_forward (struct hrtimer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_get_expires (struct hrtimer*) ; 
 int /*<<< orphan*/  hrtimer_get_softexpires (struct hrtimer*) ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long ktime_to_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void start_bandwidth_timer(struct hrtimer *period_timer, ktime_t period)
{
	unsigned long delta;
	ktime_t soft, hard, now;

	for (;;) {
		if (hrtimer_active(period_timer))
			break;

		now = hrtimer_cb_get_time(period_timer);
		hrtimer_forward(period_timer, now, period);

		soft = hrtimer_get_softexpires(period_timer);
		hard = hrtimer_get_expires(period_timer);
		delta = ktime_to_ns(ktime_sub(hard, soft));
		__hrtimer_start_range_ns(period_timer, soft, delta,
					 HRTIMER_MODE_ABS_PINNED, 0);
	}
}