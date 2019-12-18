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
 int /*<<< orphan*/  REG_CLR_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_CNTL_WDTCONFIG0_REG ; 
 int /*<<< orphan*/  RTC_CNTL_WDTFEED_REG ; 
 int /*<<< orphan*/  RTC_CNTL_WDT_EN ; 
 int /*<<< orphan*/  RTC_CNTL_WDT_FEED ; 
 int /*<<< orphan*/  RTC_CNTL_WDT_FLASHBOOT_MOD_EN ; 
 int /*<<< orphan*/  RTC_WDT_STAGE0 ; 
 int /*<<< orphan*/  RTC_WDT_STAGE1 ; 
 int /*<<< orphan*/  RTC_WDT_STAGE2 ; 
 int /*<<< orphan*/  RTC_WDT_STAGE3 ; 
 int /*<<< orphan*/  RTC_WDT_STAGE_ACTION_OFF ; 
 int rtc_wdt_get_protect_status () ; 
 int /*<<< orphan*/  rtc_wdt_protect_off () ; 
 int /*<<< orphan*/  rtc_wdt_protect_on () ; 
 int /*<<< orphan*/  rtc_wdt_set_stage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtc_wdt_disable(void)
{
    bool protect = rtc_wdt_get_protect_status();
    if (protect) {
        rtc_wdt_protect_off();
    }
    REG_SET_BIT(RTC_CNTL_WDTFEED_REG, RTC_CNTL_WDT_FEED);
    rtc_wdt_set_stage(RTC_WDT_STAGE0, RTC_WDT_STAGE_ACTION_OFF);
    rtc_wdt_set_stage(RTC_WDT_STAGE1, RTC_WDT_STAGE_ACTION_OFF);
    rtc_wdt_set_stage(RTC_WDT_STAGE2, RTC_WDT_STAGE_ACTION_OFF);
    rtc_wdt_set_stage(RTC_WDT_STAGE3, RTC_WDT_STAGE_ACTION_OFF);
    REG_CLR_BIT(RTC_CNTL_WDTCONFIG0_REG, RTC_CNTL_WDT_FLASHBOOT_MOD_EN);
    REG_CLR_BIT(RTC_CNTL_WDTCONFIG0_REG, RTC_CNTL_WDT_EN);
    if (protect) {
        rtc_wdt_protect_on();
    }
}