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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ rtc_wdt_stage_t ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_CNTL_WDTCONFIG1_REG ; 
 int /*<<< orphan*/  RTC_CNTL_WDTCONFIG2_REG ; 
 int /*<<< orphan*/  RTC_CNTL_WDTCONFIG3_REG ; 
 int /*<<< orphan*/  RTC_CNTL_WDTCONFIG4_REG ; 
 scalar_t__ RTC_WDT_STAGE0 ; 
 scalar_t__ RTC_WDT_STAGE1 ; 
 scalar_t__ RTC_WDT_STAGE2 ; 

__attribute__((used)) static uint32_t get_addr_reg(rtc_wdt_stage_t stage)
{
    uint32_t reg;
    if (stage == RTC_WDT_STAGE0) {
        reg = RTC_CNTL_WDTCONFIG1_REG;
    } else if (stage == RTC_WDT_STAGE1) {
        reg = RTC_CNTL_WDTCONFIG2_REG;
    } else if (stage == RTC_WDT_STAGE2) {
        reg = RTC_CNTL_WDTCONFIG3_REG;
    } else {
    	reg = RTC_CNTL_WDTCONFIG4_REG;
    }
    return reg;
}