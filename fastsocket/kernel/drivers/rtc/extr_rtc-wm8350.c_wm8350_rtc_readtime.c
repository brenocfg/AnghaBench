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
typedef  int u16 ;
typedef  int /*<<< orphan*/  time1 ;
struct wm8350 {int dummy; } ;
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_wday; int tm_mon; int tm_mday; int tm_year; int /*<<< orphan*/  tm_yday; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int WM8350_GET_TIME_RETRIES ; 
 int WM8350_RTC_DATE_MASK ; 
 int WM8350_RTC_DAY_SHIFT ; 
 int WM8350_RTC_HRS_MASK ; 
 int WM8350_RTC_MINS_MASK ; 
 int WM8350_RTC_MINS_SHIFT ; 
 int WM8350_RTC_MTH_MASK ; 
 int WM8350_RTC_MTH_SHIFT ; 
 int /*<<< orphan*/  WM8350_RTC_SECONDS_MINUTES ; 
 int WM8350_RTC_SECS_MASK ; 
 int WM8350_RTC_YHUNDREDS_MASK ; 
 int WM8350_RTC_YHUNDREDS_SHIFT ; 
 int WM8350_RTC_YUNITS_MASK ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int,int,int,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct wm8350* dev_get_drvdata (struct device*) ; 
 scalar_t__ memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  rtc_year_days (int,int,int) ; 
 int wm8350_block_read (struct wm8350*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int wm8350_rtc_readtime(struct device *dev, struct rtc_time *tm)
{
	struct wm8350 *wm8350 = dev_get_drvdata(dev);
	u16 time1[4], time2[4];
	int retries = WM8350_GET_TIME_RETRIES, ret;

	/*
	 * Read the time twice and compare.
	 * If time1 == time2, then time is valid else retry.
	 */
	do {
		ret = wm8350_block_read(wm8350, WM8350_RTC_SECONDS_MINUTES,
					4, time1);
		if (ret < 0)
			return ret;
		ret = wm8350_block_read(wm8350, WM8350_RTC_SECONDS_MINUTES,
					4, time2);
		if (ret < 0)
			return ret;

		if (memcmp(time1, time2, sizeof(time1)) == 0) {
			tm->tm_sec = time1[0] & WM8350_RTC_SECS_MASK;

			tm->tm_min = (time1[0] & WM8350_RTC_MINS_MASK)
			    >> WM8350_RTC_MINS_SHIFT;

			tm->tm_hour = time1[1] & WM8350_RTC_HRS_MASK;

			tm->tm_wday = ((time1[1] >> WM8350_RTC_DAY_SHIFT)
				       & 0x7) - 1;

			tm->tm_mon = ((time1[2] & WM8350_RTC_MTH_MASK)
				      >> WM8350_RTC_MTH_SHIFT) - 1;

			tm->tm_mday = (time1[2] & WM8350_RTC_DATE_MASK);

			tm->tm_year = ((time1[3] & WM8350_RTC_YHUNDREDS_MASK)
				       >> WM8350_RTC_YHUNDREDS_SHIFT) * 100;
			tm->tm_year += time1[3] & WM8350_RTC_YUNITS_MASK;

			tm->tm_yday = rtc_year_days(tm->tm_mday, tm->tm_mon,
						    tm->tm_year);
			tm->tm_year -= 1900;

			dev_dbg(dev, "Read (%d left): %04x %04x %04x %04x\n",
				retries,
				time1[0], time1[1], time1[2], time1[3]);

			return 0;
		}
	} while (retries--);

	dev_err(dev, "timed out reading RTC time\n");
	return -EIO;
}