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
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;
struct ab3100 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB3100_RTC ; 
 int AB3100_RTC_CLOCK_RATE ; 
 int /*<<< orphan*/  AB3100_TI0 ; 
 int EINVAL ; 
 int ab3100_get_register_interruptible (struct ab3100*,int /*<<< orphan*/ ,int*) ; 
 int ab3100_get_register_page_interruptible (struct ab3100*,int /*<<< orphan*/ ,int*,int) ; 
 struct ab3100* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  rtc_time_to_tm (unsigned long,struct rtc_time*) ; 
 int rtc_valid_tm (struct rtc_time*) ; 

__attribute__((used)) static int ab3100_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct ab3100 *ab3100_data = dev_get_drvdata(dev);
	unsigned long time;
	u8 rtcval;
	int err;

	err = ab3100_get_register_interruptible(ab3100_data,
						AB3100_RTC, &rtcval);
	if (err)
		return err;

	if (!(rtcval & 0x01)) {
		dev_info(dev, "clock not set (lost power)");
		return -EINVAL;
	} else {
		u64 fat_time;
		u8 buf[6];

		/* Read out time registers */
		err = ab3100_get_register_page_interruptible(ab3100_data,
							     AB3100_TI0,
							     buf, 6);
		if (err != 0)
			return err;

		fat_time = ((u64) buf[5] << 40) | ((u64) buf[4] << 32) |
			((u64) buf[3] << 24) | ((u64) buf[2] << 16) |
			((u64) buf[1] << 8) | (u64) buf[0];
		time = (unsigned long) (fat_time /
					(u64) (AB3100_RTC_CLOCK_RATE * 2));
	}

	rtc_time_to_tm(time, tm);

	return rtc_valid_tm(tm);
}