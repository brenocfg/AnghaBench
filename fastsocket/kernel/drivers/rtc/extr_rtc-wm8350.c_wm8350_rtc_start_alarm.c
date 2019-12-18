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

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  WM8350_RTC_ALMSET ; 
 int WM8350_RTC_ALMSTS ; 
 int /*<<< orphan*/  WM8350_RTC_TIME_CONTROL ; 
 int WM8350_SET_ALM_RETRIES ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int /*<<< orphan*/ ) ; 
 int wm8350_clear_bits (struct wm8350*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wm8350_reg_read (struct wm8350*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8350_rtc_start_alarm(struct wm8350 *wm8350)
{
	int ret;
	int retries = WM8350_SET_ALM_RETRIES;
	u16 rtc_ctrl;

	ret = wm8350_clear_bits(wm8350, WM8350_RTC_TIME_CONTROL,
				WM8350_RTC_ALMSET);
	if (ret < 0)
		return ret;

	/* Wait until confirmation */
	do {
		rtc_ctrl = wm8350_reg_read(wm8350, WM8350_RTC_TIME_CONTROL);
		schedule_timeout_uninterruptible(msecs_to_jiffies(1));
	} while (retries-- && rtc_ctrl & WM8350_RTC_ALMSTS);

	if (rtc_ctrl & WM8350_RTC_ALMSTS)
		return -ETIMEDOUT;

	return 0;
}