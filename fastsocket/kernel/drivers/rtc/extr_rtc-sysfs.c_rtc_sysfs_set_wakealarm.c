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
struct rtc_wkalrm {int enabled; int /*<<< orphan*/  time; } ;
struct rtc_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EBUSY ; 
 scalar_t__ rtc_read_alarm (struct rtc_device*,struct rtc_wkalrm*) ; 
 scalar_t__ rtc_read_time (struct rtc_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ rtc_set_alarm (struct rtc_device*,struct rtc_wkalrm*) ; 
 int /*<<< orphan*/  rtc_time_to_tm (unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_tm_to_time (int /*<<< orphan*/ *,unsigned long*) ; 
 unsigned long simple_strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rtc_device* to_rtc_device (struct device*) ; 

__attribute__((used)) static ssize_t
rtc_sysfs_set_wakealarm(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t n)
{
	ssize_t retval;
	unsigned long now, alarm;
	struct rtc_wkalrm alm;
	struct rtc_device *rtc = to_rtc_device(dev);
	char *buf_ptr;
	int adjust = 0;

	/* Only request alarms that trigger in the future.  Disable them
	 * by writing another time, e.g. 0 meaning Jan 1 1970 UTC.
	 */
	retval = rtc_read_time(rtc, &alm.time);
	if (retval < 0)
		return retval;
	rtc_tm_to_time(&alm.time, &now);

	buf_ptr = (char *)buf;
	if (*buf_ptr == '+') {
		buf_ptr++;
		adjust = 1;
	}
	alarm = simple_strtoul(buf_ptr, NULL, 0);
	if (adjust) {
		alarm += now;
	}
	if (alarm > now) {
		/* Avoid accidentally clobbering active alarms; we can't
		 * entirely prevent that here, without even the minimal
		 * locking from the /dev/rtcN api.
		 */
		retval = rtc_read_alarm(rtc, &alm);
		if (retval < 0)
			return retval;
		if (alm.enabled)
			return -EBUSY;

		alm.enabled = 1;
	} else {
		alm.enabled = 0;

		/* Provide a valid future alarm time.  Linux isn't EFI,
		 * this time won't be ignored when disabling the alarm.
		 */
		alarm = now + 300;
	}
	rtc_time_to_tm(alarm, &alm.time);

	retval = rtc_set_alarm(rtc, &alm);
	return (retval < 0) ? retval : n;
}