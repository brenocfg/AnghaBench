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
typedef  int rtc_wdt_reset_sig_t ;
typedef  int rtc_wdt_length_sig_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTC_CNTL_WDTCONFIG0_REG ; 
 int /*<<< orphan*/  RTC_CNTL_WDT_CPU_RESET_LENGTH ; 
 int /*<<< orphan*/  RTC_CNTL_WDT_SYS_RESET_LENGTH ; 

esp_err_t rtc_wdt_set_length_of_reset_signal(rtc_wdt_reset_sig_t reset_src, rtc_wdt_length_sig_t reset_signal_length)
{
    if (reset_src > 1 || reset_signal_length > 7) {
        return ESP_ERR_INVALID_ARG;
    }
    if (reset_src == 0) {
        REG_SET_FIELD(RTC_CNTL_WDTCONFIG0_REG, RTC_CNTL_WDT_SYS_RESET_LENGTH, reset_signal_length);
    } else {
        REG_SET_FIELD(RTC_CNTL_WDTCONFIG0_REG, RTC_CNTL_WDT_CPU_RESET_LENGTH, reset_signal_length);
    }

    return ESP_OK;
}