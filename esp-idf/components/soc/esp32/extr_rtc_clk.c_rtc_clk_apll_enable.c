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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  APLL_CAL_DELAY_1 ; 
 int /*<<< orphan*/  APLL_CAL_DELAY_2 ; 
 int /*<<< orphan*/  APLL_CAL_DELAY_3 ; 
 int /*<<< orphan*/  APLL_SDM_STOP_VAL_1 ; 
 int /*<<< orphan*/  APLL_SDM_STOP_VAL_2_REV0 ; 
 int /*<<< orphan*/  APLL_SDM_STOP_VAL_2_REV1 ; 
 int /*<<< orphan*/  EFUSE_BLK0_RDATA3_REG ; 
 scalar_t__ GET_PERI_REG_BITS2 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  I2C_APLL ; 
 int /*<<< orphan*/  I2C_APLL_DSDM0 ; 
 int /*<<< orphan*/  I2C_APLL_DSDM1 ; 
 int /*<<< orphan*/  I2C_APLL_DSDM2 ; 
 int /*<<< orphan*/  I2C_APLL_IR_CAL_DELAY ; 
 int /*<<< orphan*/  I2C_APLL_OR_CAL_END ; 
 int /*<<< orphan*/  I2C_APLL_OR_OUTPUT_DIV ; 
 int /*<<< orphan*/  I2C_APLL_SDM_STOP ; 
 int /*<<< orphan*/  I2C_READREG_MASK_RTC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2C_WRITEREG_MASK_RTC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  I2C_WRITEREG_RTC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_CLR_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ REG_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTC_CNTL_ANA_CONF_REG ; 
 int /*<<< orphan*/  RTC_CNTL_BIAS_I2C_FORCE_PD ; 
 int /*<<< orphan*/  RTC_CNTL_CLK_CONF_REG ; 
 int /*<<< orphan*/  RTC_CNTL_OPTIONS0_REG ; 
 int /*<<< orphan*/  RTC_CNTL_PLLA_FORCE_PD ; 
 int /*<<< orphan*/  RTC_CNTL_PLLA_FORCE_PU ; 
 int /*<<< orphan*/  RTC_CNTL_SOC_CLK_SEL ; 
 scalar_t__ RTC_CNTL_SOC_CLK_SEL_PLL ; 
 int /*<<< orphan*/  ets_delay_us (int) ; 

void rtc_clk_apll_enable(bool enable, uint32_t sdm0, uint32_t sdm1, uint32_t sdm2, uint32_t o_div)
{
    REG_SET_FIELD(RTC_CNTL_ANA_CONF_REG, RTC_CNTL_PLLA_FORCE_PD, enable ? 0 : 1);
    REG_SET_FIELD(RTC_CNTL_ANA_CONF_REG, RTC_CNTL_PLLA_FORCE_PU, enable ? 1 : 0);

    if (!enable &&
        REG_GET_FIELD(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_SOC_CLK_SEL) != RTC_CNTL_SOC_CLK_SEL_PLL) {
        REG_SET_BIT(RTC_CNTL_OPTIONS0_REG, RTC_CNTL_BIAS_I2C_FORCE_PD);
    } else {
        REG_CLR_BIT(RTC_CNTL_OPTIONS0_REG, RTC_CNTL_BIAS_I2C_FORCE_PD);
    }

    if (enable) {
        uint8_t sdm_stop_val_2 = APLL_SDM_STOP_VAL_2_REV1;
        uint32_t is_rev0 = (GET_PERI_REG_BITS2(EFUSE_BLK0_RDATA3_REG, 1, 15) == 0);
        if (is_rev0) {
            sdm0 = 0;
            sdm1 = 0;
            sdm_stop_val_2 = APLL_SDM_STOP_VAL_2_REV0;
        }
        I2C_WRITEREG_MASK_RTC(I2C_APLL, I2C_APLL_DSDM2, sdm2);
        I2C_WRITEREG_MASK_RTC(I2C_APLL, I2C_APLL_DSDM0, sdm0);
        I2C_WRITEREG_MASK_RTC(I2C_APLL, I2C_APLL_DSDM1, sdm1);
        I2C_WRITEREG_RTC(I2C_APLL, I2C_APLL_SDM_STOP, APLL_SDM_STOP_VAL_1);
        I2C_WRITEREG_RTC(I2C_APLL, I2C_APLL_SDM_STOP, sdm_stop_val_2);
        I2C_WRITEREG_MASK_RTC(I2C_APLL, I2C_APLL_OR_OUTPUT_DIV, o_div);

        /* calibration */
        I2C_WRITEREG_RTC(I2C_APLL, I2C_APLL_IR_CAL_DELAY, APLL_CAL_DELAY_1);
        I2C_WRITEREG_RTC(I2C_APLL, I2C_APLL_IR_CAL_DELAY, APLL_CAL_DELAY_2);
        I2C_WRITEREG_RTC(I2C_APLL, I2C_APLL_IR_CAL_DELAY, APLL_CAL_DELAY_3);

        /* wait for calibration end */
        while (!(I2C_READREG_MASK_RTC(I2C_APLL, I2C_APLL_OR_CAL_END))) {
            /* use ets_delay_us so the RTC bus doesn't get flooded */
            ets_delay_us(1);
        }
    }
}