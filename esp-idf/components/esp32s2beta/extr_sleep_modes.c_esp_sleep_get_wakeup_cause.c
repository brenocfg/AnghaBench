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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  esp_sleep_wakeup_cause_t ;

/* Variables and functions */
 scalar_t__ DEEPSLEEP_RESET ; 
 int /*<<< orphan*/  ESP_SLEEP_WAKEUP_EXT0 ; 
 int /*<<< orphan*/  ESP_SLEEP_WAKEUP_EXT1 ; 
 int /*<<< orphan*/  ESP_SLEEP_WAKEUP_TIMER ; 
 int /*<<< orphan*/  ESP_SLEEP_WAKEUP_TOUCHPAD ; 
 int /*<<< orphan*/  ESP_SLEEP_WAKEUP_ULP ; 
 int /*<<< orphan*/  ESP_SLEEP_WAKEUP_UNDEFINED ; 
 int REG_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_CNTL_WAKEUP_CAUSE ; 
 int /*<<< orphan*/  RTC_CNTL_WAKEUP_STATE_REG ; 
 int RTC_EXT0_TRIG_EN ; 
 int RTC_EXT1_TRIG_EN ; 
 int RTC_TIMER_TRIG_EN ; 
 int RTC_TOUCH_TRIG_EN ; 
 int RTC_ULP_TRIG_EN ; 
 scalar_t__ rtc_get_reset_reason (int /*<<< orphan*/ ) ; 

esp_sleep_wakeup_cause_t esp_sleep_get_wakeup_cause(void)
{
    if (rtc_get_reset_reason(0) != DEEPSLEEP_RESET) {
        return ESP_SLEEP_WAKEUP_UNDEFINED;
    }

    uint32_t wakeup_cause = REG_GET_FIELD(RTC_CNTL_WAKEUP_STATE_REG, RTC_CNTL_WAKEUP_CAUSE);
    if (wakeup_cause & RTC_EXT0_TRIG_EN) {
        return ESP_SLEEP_WAKEUP_EXT0;
    } else if (wakeup_cause & RTC_EXT1_TRIG_EN) {
        return ESP_SLEEP_WAKEUP_EXT1;
    } else if (wakeup_cause & RTC_TIMER_TRIG_EN) {
        return ESP_SLEEP_WAKEUP_TIMER;
    } else if (wakeup_cause & RTC_TOUCH_TRIG_EN) {
        return ESP_SLEEP_WAKEUP_TOUCHPAD;
    } else if (wakeup_cause & RTC_ULP_TRIG_EN) {
        return ESP_SLEEP_WAKEUP_ULP;
    } else {
        return ESP_SLEEP_WAKEUP_UNDEFINED;
    }
}