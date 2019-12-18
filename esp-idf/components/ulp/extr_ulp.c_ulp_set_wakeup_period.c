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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ REG_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_FIELD (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ RTC_CLK_CAL_FRACT ; 
 int /*<<< orphan*/  RTC_CNTL_TIMER2_REG ; 
 int /*<<< orphan*/  RTC_CNTL_ULPCP_TOUCH_START_WAIT ; 
 int /*<<< orphan*/  SENS_SLEEP_CYCLES_S0 ; 
 scalar_t__ SENS_ULP_CP_SLEEP_CYC0_REG ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ ULP_FSM_PREPARE_SLEEP_CYCLES ; 
 scalar_t__ ULP_FSM_WAKEUP_SLEEP_CYCLES ; 
 scalar_t__ esp_clk_slowclk_cal_get () ; 

esp_err_t ulp_set_wakeup_period(size_t period_index, uint32_t period_us)
{
#if CONFIG_IDF_TARGET_ESP32
    if (period_index > 4) {
        return ESP_ERR_INVALID_ARG;
    }
    uint64_t period_us_64 = period_us;
    uint64_t period_cycles = (period_us_64 << RTC_CLK_CAL_FRACT) / esp_clk_slowclk_cal_get();
    uint64_t min_sleep_period_cycles = ULP_FSM_PREPARE_SLEEP_CYCLES
                                    + ULP_FSM_WAKEUP_SLEEP_CYCLES
                                    + REG_GET_FIELD(RTC_CNTL_TIMER2_REG, RTC_CNTL_ULPCP_TOUCH_START_WAIT);
    if (period_cycles < min_sleep_period_cycles) {
        period_cycles = 0;
        ESP_LOGW(TAG, "Sleep period clipped to minimum of %d cycles", (uint32_t) min_sleep_period_cycles);
    } else {
        period_cycles -= min_sleep_period_cycles;
    }
    REG_SET_FIELD(SENS_ULP_CP_SLEEP_CYC0_REG + period_index * sizeof(uint32_t),
            SENS_SLEEP_CYCLES_S0, (uint32_t) period_cycles);
#endif
    return ESP_OK;
}