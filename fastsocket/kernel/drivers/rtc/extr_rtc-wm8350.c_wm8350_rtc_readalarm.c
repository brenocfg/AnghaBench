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
struct wm8350 {int dummy; } ;
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_wday; int tm_mon; int tm_mday; int tm_year; } ;
struct rtc_wkalrm {int enabled; struct rtc_time time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8350_ALARM_SECONDS_MINUTES ; 
 int WM8350_RTC_ALMDATE_MASK ; 
 int WM8350_RTC_ALMDAY_SHIFT ; 
 int WM8350_RTC_ALMHRS_MASK ; 
 int WM8350_RTC_ALMMINS_MASK ; 
 int WM8350_RTC_ALMMINS_SHIFT ; 
 int WM8350_RTC_ALMMTH_MASK ; 
 int WM8350_RTC_ALMMTH_SHIFT ; 
 int WM8350_RTC_ALMSECS_MASK ; 
 int WM8350_RTC_ALMSTS ; 
 struct wm8350* dev_get_drvdata (struct device*) ; 
 int wm8350_block_read (struct wm8350*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int wm8350_rtc_readalarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct wm8350 *wm8350 = dev_get_drvdata(dev);
	struct rtc_time *tm = &alrm->time;
	u16 time[4];
	int ret;

	ret = wm8350_block_read(wm8350, WM8350_ALARM_SECONDS_MINUTES, 4, time);
	if (ret < 0)
		return ret;

	tm->tm_sec = time[0] & WM8350_RTC_ALMSECS_MASK;
	if (tm->tm_sec == WM8350_RTC_ALMSECS_MASK)
		tm->tm_sec = -1;

	tm->tm_min = time[0] & WM8350_RTC_ALMMINS_MASK;
	if (tm->tm_min == WM8350_RTC_ALMMINS_MASK)
		tm->tm_min = -1;
	else
		tm->tm_min >>= WM8350_RTC_ALMMINS_SHIFT;

	tm->tm_hour = time[1] & WM8350_RTC_ALMHRS_MASK;
	if (tm->tm_hour == WM8350_RTC_ALMHRS_MASK)
		tm->tm_hour = -1;

	tm->tm_wday = ((time[1] >> WM8350_RTC_ALMDAY_SHIFT) & 0x7) - 1;
	if (tm->tm_wday > 7)
		tm->tm_wday = -1;

	tm->tm_mon = time[2] & WM8350_RTC_ALMMTH_MASK;
	if (tm->tm_mon == WM8350_RTC_ALMMTH_MASK)
		tm->tm_mon = -1;
	else
		tm->tm_mon = (tm->tm_mon >> WM8350_RTC_ALMMTH_SHIFT) - 1;

	tm->tm_mday = (time[2] & WM8350_RTC_ALMDATE_MASK);
	if (tm->tm_mday == WM8350_RTC_ALMDATE_MASK)
		tm->tm_mday = -1;

	tm->tm_year = -1;

	alrm->enabled = !(time[3] & WM8350_RTC_ALMSTS);

	return 0;
}