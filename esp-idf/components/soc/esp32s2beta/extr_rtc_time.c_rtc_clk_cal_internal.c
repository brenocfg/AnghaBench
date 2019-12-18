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
typedef  int rtc_cal_sel_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GET_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MHZ ; 
 int REG_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int RTC_CAL_32K_XTAL ; 
 int RTC_CAL_8MD256 ; 
 int /*<<< orphan*/  RTC_CNTL_CLK_CONF_REG ; 
 int /*<<< orphan*/  RTC_CNTL_DIG_CLK8M_D256_EN ; 
 int /*<<< orphan*/  RTC_CNTL_DIG_XTAL32K_EN ; 
 int RTC_FAST_CLK_FREQ_APPROX ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMG_RTCCALICFG1_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMG_RTCCALICFG2_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMG_RTCCALICFG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMG_RTC_CALI_CLK_SEL ; 
 int /*<<< orphan*/  TIMG_RTC_CALI_MAX ; 
 int /*<<< orphan*/  TIMG_RTC_CALI_RDY ; 
 int /*<<< orphan*/  TIMG_RTC_CALI_START ; 
 int /*<<< orphan*/  TIMG_RTC_CALI_START_CYCLING ; 
 int /*<<< orphan*/  TIMG_RTC_CALI_TIMEOUT ; 
 int /*<<< orphan*/  TIMG_RTC_CALI_TIMEOUT_THRES ; 
 int /*<<< orphan*/  TIMG_RTC_CALI_VALUE ; 
 int /*<<< orphan*/  ets_delay_us (int) ; 

uint32_t rtc_clk_cal_internal(rtc_cal_sel_t cal_clk, uint32_t slowclk_cycles)
{
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
    /* There may be another calibration process already running during we call this function,
     * so we should wait the last process is done.
     */
    if (!GET_PERI_REG_MASK(TIMG_RTCCALICFG2_REG(0), TIMG_RTC_CALI_TIMEOUT)) {
        if (GET_PERI_REG_MASK(TIMG_RTCCALICFG_REG(0), TIMG_RTC_CALI_START_CYCLING)) {
            while(!GET_PERI_REG_MASK(TIMG_RTCCALICFG_REG(0), TIMG_RTC_CALI_RDY));
        }
    }
    CLEAR_PERI_REG_MASK(TIMG_RTCCALICFG_REG(0), TIMG_RTC_CALI_START_CYCLING);
    REG_SET_FIELD(TIMG_RTCCALICFG_REG(0), TIMG_RTC_CALI_MAX, slowclk_cycles);
    /* Figure out how long to wait for calibration to finish */

    /* Set timeout reg and expect time delay*/
    uint32_t expected_freq;
    if (cal_clk == RTC_CAL_32K_XTAL) {
        REG_SET_FIELD(TIMG_RTCCALICFG2_REG(0), TIMG_RTC_CALI_TIMEOUT_THRES, (slowclk_cycles << 13));
        expected_freq = 32768;
    } else if (cal_clk == RTC_CAL_8MD256) {
        REG_SET_FIELD(TIMG_RTCCALICFG2_REG(0), TIMG_RTC_CALI_TIMEOUT_THRES, (slowclk_cycles << 13));
        expected_freq = RTC_FAST_CLK_FREQ_APPROX / 256;
    } else {
        REG_SET_FIELD(TIMG_RTCCALICFG2_REG(0), TIMG_RTC_CALI_TIMEOUT_THRES, (slowclk_cycles << 11));
        expected_freq = 90000;
    }
    uint32_t us_time_estimate = (uint32_t) (((uint64_t) slowclk_cycles) * MHZ / expected_freq);
    /* Start calibration */
    CLEAR_PERI_REG_MASK(TIMG_RTCCALICFG_REG(0), TIMG_RTC_CALI_START);
    SET_PERI_REG_MASK(TIMG_RTCCALICFG_REG(0), TIMG_RTC_CALI_START);

    /* Wait for calibration to finish up to another us_time_estimate */
    ets_delay_us(us_time_estimate);
    uint32_t cal_val;
    while (true) {
        if (GET_PERI_REG_MASK(TIMG_RTCCALICFG_REG(0), TIMG_RTC_CALI_RDY)) {
            cal_val = REG_GET_FIELD(TIMG_RTCCALICFG1_REG(0), TIMG_RTC_CALI_VALUE);
            break;
        }
        if (GET_PERI_REG_MASK(TIMG_RTCCALICFG2_REG(0), TIMG_RTC_CALI_TIMEOUT)) {
            cal_val = 0;
            break;
        }
    }
    CLEAR_PERI_REG_MASK(TIMG_RTCCALICFG_REG(0), TIMG_RTC_CALI_START);

    REG_SET_FIELD(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_DIG_XTAL32K_EN, dig_32k_xtal_state);

    if (cal_clk == RTC_CAL_8MD256) {
        CLEAR_PERI_REG_MASK(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_DIG_CLK8M_D256_EN);
    }

    return cal_val;
}