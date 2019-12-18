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
typedef  int uint8_t ;
typedef  int rtc_xtal_freq_t ;
typedef  scalar_t__ rtc_pll_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPORT_CPU_PER_CONF_REG ; 
 int /*<<< orphan*/  DPORT_PLL_FREQ_SEL ; 
 int /*<<< orphan*/  I2C_BBPLL ; 
 int /*<<< orphan*/  I2C_BBPLL_IR_CAL_ENX_CAP ; 
 int /*<<< orphan*/  I2C_BBPLL_IR_CAL_EXT_CAP ; 
 int /*<<< orphan*/  I2C_BBPLL_MODE_HF ; 
 int I2C_BBPLL_OC_DCHGP_LSB ; 
 int /*<<< orphan*/  I2C_BBPLL_OC_DCUR ; 
 int I2C_BBPLL_OC_DHREF_SEL_LSB ; 
 int /*<<< orphan*/  I2C_BBPLL_OC_DIV_7_0 ; 
 int I2C_BBPLL_OC_DLREF_SEL_LSB ; 
 int /*<<< orphan*/  I2C_BBPLL_OC_DR1 ; 
 int /*<<< orphan*/  I2C_BBPLL_OC_DR3 ; 
 int /*<<< orphan*/  I2C_BBPLL_OC_REF_DIV ; 
 int /*<<< orphan*/  I2C_BBPLL_OR_CAL_CAP ; 
 int I2C_READREG_MASK_RTC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2C_WRITEREG_MASK_RTC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  I2C_WRITEREG_RTC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ RTC_PLL_480M ; 
#define  RTC_XTAL_FREQ_24M 130 
#define  RTC_XTAL_FREQ_26M 129 
#define  RTC_XTAL_FREQ_40M 128 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 

void rtc_clk_bbpll_set(rtc_xtal_freq_t xtal_freq, rtc_pll_t pll_freq)
{
    uint8_t div_ref;
    uint8_t div7_0;
    uint8_t dr1;
    uint8_t dr3;
    uint8_t dchgp;
    uint8_t dcur;

    if (pll_freq == RTC_PLL_480M) {
        /* Raise the voltage, if needed */
        /* move to 240M logic */
        //REG_SET_FIELD(RTC_CNTL_REG, RTC_CNTL_DIG_DBIAS_WAK, DIG_DBIAS_80M_160M);
        /* Set this register to let digital know pll is 480M */
        SET_PERI_REG_MASK(DPORT_CPU_PER_CONF_REG, DPORT_PLL_FREQ_SEL);
        /* Configure 480M PLL */
        switch (xtal_freq) {
            case RTC_XTAL_FREQ_40M:
                div_ref = 0;
                div7_0 = 8;
                dr1 = 0;
                dr3 = 0;
                dchgp = 5;
                dcur = 4;
                break;
            case RTC_XTAL_FREQ_26M:
                div_ref = 12;
                div7_0 = 156;
                dr1 = 3;
                dr3 = 3;
                dchgp = 4;
                dcur = 1;
                break;
            case RTC_XTAL_FREQ_24M:
                div_ref = 11;
                div7_0 = 156;
                dr1 = 3;
                dr3 = 3;
                dchgp = 4;
                dcur = 1;
                break;
            default:
                div_ref = 0;
                div7_0 = 8;
                dr1 = 0;
                dr3 = 0;
                dchgp = 5;
                dcur = 4;
                break;
        }
        I2C_WRITEREG_RTC(I2C_BBPLL, I2C_BBPLL_MODE_HF, 0x6B);
    } else {
        /* Raise the voltage */
        //REG_SET_FIELD(RTC_CNTL_REG, RTC_CNTL_DIG_DBIAS_WAK, DIG_DBIAS_240M);
        //ets_delay_us(DELAY_PLL_DBIAS_RAISE);
        CLEAR_PERI_REG_MASK(DPORT_CPU_PER_CONF_REG, DPORT_PLL_FREQ_SEL);
        /* Configure 480M PLL */
        switch (xtal_freq) {
            case RTC_XTAL_FREQ_40M:
                div_ref = 0;
                div7_0 = 4;
                dr1 = 0;
                dr3 = 0;
                dchgp = 5;
                dcur = 5;
                break;
            case RTC_XTAL_FREQ_26M:
                div_ref = 12;
                div7_0 = 236;
                dr1 = 3;
                dr3 = 3;
                dchgp = 0;
                dcur = 2;
                break;
            case RTC_XTAL_FREQ_24M:
                div_ref = 11;
                div7_0 = 236;
                dr1 = 3;
                dr3 = 3;
                dchgp = 0;
                dcur = 2;
                break;
            default:
                div_ref = 0;
                div7_0 = 4;
                dr1 = 0;
                dr3 = 0;
                dchgp = 5;
                dcur = 5;
                break;
        }
        I2C_WRITEREG_RTC(I2C_BBPLL, I2C_BBPLL_MODE_HF, 0x69);
    }
    uint8_t i2c_bbpll_lref  = (dchgp << I2C_BBPLL_OC_DCHGP_LSB) | (div_ref);
    uint8_t i2c_bbpll_div_7_0 = div7_0;
    uint8_t i2c_bbpll_dcur = (2 << I2C_BBPLL_OC_DLREF_SEL_LSB ) | (1 << I2C_BBPLL_OC_DHREF_SEL_LSB) | dcur;
    I2C_WRITEREG_RTC(I2C_BBPLL, I2C_BBPLL_OC_REF_DIV, i2c_bbpll_lref);
    I2C_WRITEREG_RTC(I2C_BBPLL, I2C_BBPLL_OC_DIV_7_0, i2c_bbpll_div_7_0);
    I2C_WRITEREG_MASK_RTC(I2C_BBPLL, I2C_BBPLL_OC_DR1, dr1);
    I2C_WRITEREG_MASK_RTC(I2C_BBPLL, I2C_BBPLL_OC_DR3, dr3);
    I2C_WRITEREG_RTC(I2C_BBPLL, I2C_BBPLL_OC_DCUR, i2c_bbpll_dcur);

    // Enable calibration by software
    I2C_WRITEREG_MASK_RTC(I2C_BBPLL, I2C_BBPLL_IR_CAL_ENX_CAP, 1);
    for (int ext_cap = 0; ext_cap < 16; ext_cap++) {
        uint8_t cal_result;
        I2C_WRITEREG_MASK_RTC(I2C_BBPLL, I2C_BBPLL_IR_CAL_EXT_CAP, ext_cap);
        cal_result = I2C_READREG_MASK_RTC(I2C_BBPLL, I2C_BBPLL_OR_CAL_CAP);
        if (cal_result == 0) {
            break;
        }
        if(ext_cap == 15) {
            SOC_LOGE(TAG, "BBPLL SOFTWARE CAL FAIL");
        }
    }

    /* this delay is replaced by polling Pll calibration end flag
     * uint32_t delay_pll_en = (rtc_clk_slow_freq_get() == RTC_SLOW_FREQ_RTC) ?
     *       DELAY_PLL_ENABLE_WITH_150K : DELAY_PLL_ENABLE_WITH_32K;
     * ets_delay_us(delay_pll_en);
     */
    /* this calibration didn't work on 480M
    need to test exact delay according to 320M
    while (!GET_PERI_REG_MASK(I2C_MST_ANA_STATE_REG, I2C_MST_BBPLL_CAL_END)) {
        ets_delay_us(1);
    }
    */
}