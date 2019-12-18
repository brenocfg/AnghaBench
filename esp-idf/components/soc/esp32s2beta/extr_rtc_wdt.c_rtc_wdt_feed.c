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

/* Variables and functions */
 int /*<<< orphan*/  REG_SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_CNTL_WDTFEED_REG ; 
 int /*<<< orphan*/  RTC_CNTL_WDT_FEED ; 
 int rtc_wdt_get_protect_status () ; 
 int /*<<< orphan*/  rtc_wdt_protect_off () ; 
 int /*<<< orphan*/  rtc_wdt_protect_on () ; 

void rtc_wdt_feed(void)
{
    bool protect = rtc_wdt_get_protect_status();
    if (protect) {
        rtc_wdt_protect_off();
    }
    REG_SET_BIT(RTC_CNTL_WDTFEED_REG, RTC_CNTL_WDT_FEED);
    if (protect) {
        rtc_wdt_protect_on();
    }
}