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
struct bus_type {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 int /*<<< orphan*/  ap_poll_timer ; 
 int /*<<< orphan*/  hrtimer_forward (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_get_expires (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_is_queued (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_set_expires (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_start_expires (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,unsigned long long) ; 
 unsigned long long poll_timeout ; 
 int sscanf (char const*,char*,unsigned long long*) ; 

__attribute__((used)) static ssize_t poll_timeout_store(struct bus_type *bus, const char *buf,
				  size_t count)
{
	unsigned long long time;
	ktime_t hr_time;

	/* 120 seconds = maximum poll interval */
	if (sscanf(buf, "%llu\n", &time) != 1 || time < 1 ||
	    time > 120000000000ULL)
		return -EINVAL;
	poll_timeout = time;
	hr_time = ktime_set(0, poll_timeout);

	if (!hrtimer_is_queued(&ap_poll_timer) ||
	    !hrtimer_forward(&ap_poll_timer, hrtimer_get_expires(&ap_poll_timer), hr_time)) {
		hrtimer_set_expires(&ap_poll_timer, hr_time);
		hrtimer_start_expires(&ap_poll_timer, HRTIMER_MODE_ABS);
	}
	return count;
}