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
typedef  int u8 ;
typedef  int u64 ;
struct rtc_wkalrm {int enabled; int /*<<< orphan*/  time; scalar_t__ pending; } ;
struct device {int dummy; } ;
struct ab3100 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB3100_AL0 ; 
 int /*<<< orphan*/  AB3100_RTC ; 
 int AB3100_RTC_CLOCK_RATE ; 
 int ab3100_get_register_interruptible (struct ab3100*,int /*<<< orphan*/ ,int*) ; 
 int ab3100_get_register_page_interruptible (struct ab3100*,int /*<<< orphan*/ ,int*,int) ; 
 struct ab3100* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_time_to_tm (unsigned long,int /*<<< orphan*/ *) ; 
 int rtc_valid_tm (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ab3100_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct ab3100 *ab3100_data = dev_get_drvdata(dev);
	unsigned long time;
	u64 fat_time;
	u8 buf[6];
	u8 rtcval;
	int err;

	/* Figure out if alarm is enabled or not */
	err = ab3100_get_register_interruptible(ab3100_data,
						AB3100_RTC, &rtcval);
	if (err)
		return err;
	if (rtcval & 0x04)
		alarm->enabled = 1;
	else
		alarm->enabled = 0;
	/* No idea how this could be represented */
	alarm->pending = 0;
	/* Read out alarm registers, only 4 bytes */
	err = ab3100_get_register_page_interruptible(ab3100_data,
						     AB3100_AL0, buf, 4);
	if (err)
		return err;
	fat_time = ((u64) buf[3] << 40) | ((u64) buf[2] << 32) |
		((u64) buf[1] << 24) | ((u64) buf[0] << 16);
	time = (unsigned long) (fat_time / (u64) (AB3100_RTC_CLOCK_RATE * 2));

	rtc_time_to_tm(time, &alarm->time);

	return rtc_valid_tm(&alarm->time);
}