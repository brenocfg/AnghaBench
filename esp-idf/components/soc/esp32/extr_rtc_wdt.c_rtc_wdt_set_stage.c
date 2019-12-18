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
typedef  int rtc_wdt_stage_t ;
typedef  int rtc_wdt_stage_action_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTC_CNTL_WDTCONFIG0_REG ; 
 int /*<<< orphan*/  RTC_CNTL_WDT_STG0 ; 
 int /*<<< orphan*/  RTC_CNTL_WDT_STG1 ; 
 int /*<<< orphan*/  RTC_CNTL_WDT_STG2 ; 
 int /*<<< orphan*/  RTC_CNTL_WDT_STG3 ; 
 int RTC_WDT_STAGE0 ; 
 int RTC_WDT_STAGE1 ; 
 int RTC_WDT_STAGE2 ; 

esp_err_t rtc_wdt_set_stage(rtc_wdt_stage_t stage, rtc_wdt_stage_action_t stage_sel)
{
    if (stage > 3 || stage_sel > 4) {
        return ESP_ERR_INVALID_ARG;
    }
    if (stage == RTC_WDT_STAGE0) {
        REG_SET_FIELD(RTC_CNTL_WDTCONFIG0_REG, RTC_CNTL_WDT_STG0, stage_sel);
    } else if (stage == RTC_WDT_STAGE1) {
        REG_SET_FIELD(RTC_CNTL_WDTCONFIG0_REG, RTC_CNTL_WDT_STG1, stage_sel);
    } else if (stage == RTC_WDT_STAGE2) {
        REG_SET_FIELD(RTC_CNTL_WDTCONFIG0_REG, RTC_CNTL_WDT_STG2, stage_sel);
    } else {
        REG_SET_FIELD(RTC_CNTL_WDTCONFIG0_REG, RTC_CNTL_WDT_STG3, stage_sel);
    }

    return ESP_OK;
}