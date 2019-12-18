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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXC_RTC_TIME ; 
 unsigned long get_alarm_or_time (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_alarm_or_time (struct device*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int mxc_rtc_set_mmss(struct device *dev, unsigned long time)
{
	/* Avoid roll-over from reading the different registers */
	do {
		set_alarm_or_time(dev, MXC_RTC_TIME, time);
	} while (time != get_alarm_or_time(dev, MXC_RTC_TIME));

	return 0;
}