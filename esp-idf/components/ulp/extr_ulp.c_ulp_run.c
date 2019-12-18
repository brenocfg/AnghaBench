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
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_CNTL_BIAS_CORE_FOLW_8M ; 
 int /*<<< orphan*/  RTC_CNTL_BIAS_I2C_FOLW_8M ; 
 int /*<<< orphan*/  RTC_CNTL_BIAS_SLEEP_FOLW_8M ; 
 int /*<<< orphan*/  RTC_CNTL_MIN_SLP_VAL ; 
 int /*<<< orphan*/  RTC_CNTL_MIN_SLP_VAL_MIN ; 
 int /*<<< orphan*/  RTC_CNTL_OPTIONS0_REG ; 
 int /*<<< orphan*/  RTC_CNTL_STATE0_REG ; 
 int /*<<< orphan*/  RTC_CNTL_TIMER5_REG ; 
 int /*<<< orphan*/  RTC_CNTL_ULP_CP_SLP_TIMER_EN ; 
 int /*<<< orphan*/  SENS_PC_INIT ; 
 int /*<<< orphan*/  SENS_SAR_START_FORCE_REG ; 
 int /*<<< orphan*/  SENS_ULP_CP_FORCE_START_TOP_M ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ets_delay_us (int) ; 

esp_err_t ulp_run(uint32_t entry_point)
{
#if CONFIG_IDF_TARGET_ESP32
    // disable ULP timer
    CLEAR_PERI_REG_MASK(RTC_CNTL_STATE0_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);
    // wait for at least 1 RTC_SLOW_CLK cycle
    ets_delay_us(10);
    // set entry point
    REG_SET_FIELD(SENS_SAR_START_FORCE_REG, SENS_PC_INIT, entry_point);
    // disable force start
    CLEAR_PERI_REG_MASK(SENS_SAR_START_FORCE_REG, SENS_ULP_CP_FORCE_START_TOP_M);
    // set time until wakeup is allowed to the smallest possible
    REG_SET_FIELD(RTC_CNTL_TIMER5_REG, RTC_CNTL_MIN_SLP_VAL, RTC_CNTL_MIN_SLP_VAL_MIN);
    // make sure voltage is raised when RTC 8MCLK is enabled
    SET_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, RTC_CNTL_BIAS_I2C_FOLW_8M);
    SET_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, RTC_CNTL_BIAS_CORE_FOLW_8M);
    SET_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, RTC_CNTL_BIAS_SLEEP_FOLW_8M);
    // enable ULP timer
    SET_PERI_REG_MASK(RTC_CNTL_STATE0_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);
#endif
    return ESP_OK;
}