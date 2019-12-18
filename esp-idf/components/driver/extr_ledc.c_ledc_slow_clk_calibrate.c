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
typedef  unsigned long long uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY_CLK8M_CLK_SWITCH ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LEDC_TAG ; 
 int /*<<< orphan*/  RTC_CAL_8MD256 ; 
 int RTC_CLK_CAL_FRACT ; 
 int /*<<< orphan*/  RTC_CNTL_CLK_CONF_REG ; 
 int /*<<< orphan*/  RTC_CNTL_DIG_CLK8M_EN_M ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLOW_CLK_CYC_CALIBRATE ; 
 int /*<<< orphan*/  ets_delay_us (int /*<<< orphan*/ ) ; 
 unsigned long long rtc_clk_cal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long long s_ledc_slow_clk_8M ; 

__attribute__((used)) static bool ledc_slow_clk_calibrate(void)
{
#ifdef CONFIG_IDF_TARGET_ESP32
    //Enable CLK8M for LEDC
    SET_PERI_REG_MASK(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_DIG_CLK8M_EN_M);
    //Waiting for CLK8M to turn on
    ets_delay_us(DELAY_CLK8M_CLK_SWITCH);
    uint32_t cal_val = rtc_clk_cal(RTC_CAL_8MD256, SLOW_CLK_CYC_CALIBRATE);
    if(cal_val == 0) {
        ESP_LOGE(LEDC_TAG, "CLK8M_CLK calibration failed");
        return false;
    }
    s_ledc_slow_clk_8M = 1000000ULL * (1 << RTC_CLK_CAL_FRACT) * 256 / cal_val;
    ESP_LOGD(LEDC_TAG, "Calibrate CLK8M_CLK : %d Hz", s_ledc_slow_clk_8M);
    return true;
#else
    ESP_LOGE(LEDC_TAG, "CLK8M source currently only supported on ESP32");
    return false;
#endif
}