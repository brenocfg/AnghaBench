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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  scalar_t__ rtc_xtal_freq_t ;
typedef  scalar_t__ rtc_slow_freq_t ;
typedef  int rtc_cal_sel_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MHZ ; 
 int REG_GET_FIELD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int,int) ; 
 int RTC_CAL_32K_XTAL ; 
 int RTC_CAL_8MD256 ; 
 int RTC_CAL_RTC_MUX ; 
 int RTC_CNTL_ANA_CLK_RTC_SEL ; 
 int /*<<< orphan*/  RTC_CNTL_CLK_CONF_REG ; 
 int /*<<< orphan*/  RTC_CNTL_DIG_CLK8M_D256_EN ; 
 int RTC_CNTL_DIG_XTAL32K_EN ; 
 int RTC_FAST_CLK_FREQ_APPROX ; 
 scalar_t__ RTC_SLOW_FREQ_32K_XTAL ; 
 scalar_t__ RTC_SLOW_FREQ_8MD256 ; 
 scalar_t__ RTC_XTAL_FREQ_40M ; 
 scalar_t__ RTC_XTAL_FREQ_AUTO ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TIMG_RTCCALICFG1_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMG_RTCCALICFG_REG (int /*<<< orphan*/ ) ; 
 int TIMG_RTC_CALI_CLK_SEL ; 
 int TIMG_RTC_CALI_MAX ; 
 int /*<<< orphan*/  TIMG_RTC_CALI_RDY ; 
 int /*<<< orphan*/  TIMG_RTC_CALI_START ; 
 int /*<<< orphan*/  TIMG_RTC_CALI_START_CYCLING ; 
 int TIMG_RTC_CALI_VALUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ets_delay_us (int) ; 
 scalar_t__ rtc_clk_xtal_freq_get () ; 

__attribute__((used)) static uint32_t rtc_clk_cal_internal(rtc_cal_sel_t cal_clk, uint32_t slowclk_cycles)
{
    assert(slowclk_cycles < 32767);
    /* Enable requested clock (150k clock is always on) */
    int dig_32k_xtal_state = REG_GET_FIELD(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_DIG_XTAL32K_EN);
    if (cal_clk == RTC_CAL_32K_XTAL && !dig_32k_xtal_state) {
        REG_SET_FIELD(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_DIG_XTAL32K_EN, 1);
    }

    if (cal_clk == RTC_CAL_8MD256) {
        SET_PERI_REG_MASK(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_DIG_CLK8M_D256_EN);
    }
    /* Prepare calibration */
    REG_SET_FIELD(TIMG_RTCCALICFG_REG(0), TIMG_RTC_CALI_CLK_SEL, cal_clk);
    CLEAR_PERI_REG_MASK(TIMG_RTCCALICFG_REG(0), TIMG_RTC_CALI_START_CYCLING);
    REG_SET_FIELD(TIMG_RTCCALICFG_REG(0), TIMG_RTC_CALI_MAX, slowclk_cycles);
    /* Figure out how long to wait for calibration to finish */
    uint32_t expected_freq;
    rtc_slow_freq_t slow_freq = REG_GET_FIELD(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_ANA_CLK_RTC_SEL);
    if (cal_clk == RTC_CAL_32K_XTAL ||
        (cal_clk == RTC_CAL_RTC_MUX && slow_freq == RTC_SLOW_FREQ_32K_XTAL)) {
        expected_freq = 32768; /* standard 32k XTAL */
    } else if (cal_clk == RTC_CAL_8MD256 ||
            (cal_clk == RTC_CAL_RTC_MUX && slow_freq == RTC_SLOW_FREQ_8MD256)) {
        expected_freq = RTC_FAST_CLK_FREQ_APPROX / 256;
    } else {
        expected_freq = 150000; /* 150k internal oscillator */
    }
    uint32_t us_time_estimate = (uint32_t) (((uint64_t) slowclk_cycles) * MHZ / expected_freq);
    /* Check if the required number of slowclk_cycles may result in an overflow of TIMG_RTC_CALI_VALUE */
    rtc_xtal_freq_t xtal_freq = rtc_clk_xtal_freq_get();
    if (xtal_freq == RTC_XTAL_FREQ_AUTO) {
        /* XTAL frequency is not known yet; assume worst case (40 MHz) */
        xtal_freq = RTC_XTAL_FREQ_40M;
    }
    const uint32_t us_timer_max =  TIMG_RTC_CALI_VALUE / (uint32_t) xtal_freq;
    if (us_time_estimate >= us_timer_max) {
        SOC_LOGE(TAG, "slowclk_cycles value too large, possible overflow");
        return 0;
    }
    /* Start calibration */
    CLEAR_PERI_REG_MASK(TIMG_RTCCALICFG_REG(0), TIMG_RTC_CALI_START);
    SET_PERI_REG_MASK(TIMG_RTCCALICFG_REG(0), TIMG_RTC_CALI_START);
    /* Wait the expected time calibration should take.
     * TODO: if running under RTOS, and us_time_estimate > RTOS tick, use the
     * RTOS delay function.
     */
    ets_delay_us(us_time_estimate);
    /* Wait for calibration to finish up to another us_time_estimate */
    int timeout_us = us_time_estimate;
    while (!GET_PERI_REG_MASK(TIMG_RTCCALICFG_REG(0), TIMG_RTC_CALI_RDY) &&
            timeout_us > 0) {
        timeout_us--;
        ets_delay_us(1);
    }

    REG_SET_FIELD(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_DIG_XTAL32K_EN, dig_32k_xtal_state);

    if (cal_clk == RTC_CAL_8MD256) {
        CLEAR_PERI_REG_MASK(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_DIG_CLK8M_D256_EN);
    }
    if (timeout_us == 0) {
        /* timed out waiting for calibration */
        return 0;
    }

    return REG_GET_FIELD(TIMG_RTCCALICFG1_REG(0), TIMG_RTC_CALI_VALUE);
}