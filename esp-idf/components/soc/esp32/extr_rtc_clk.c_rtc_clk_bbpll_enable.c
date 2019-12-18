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

/* Variables and functions */
 int /*<<< orphan*/  BBPLL_BBADC_CAL_7_0_VAL ; 
 int /*<<< orphan*/  BBPLL_IR_CAL_DELAY_VAL ; 
 int /*<<< orphan*/  BBPLL_IR_CAL_EXT_CAP_VAL ; 
 int /*<<< orphan*/  BBPLL_OC_ENB_FCAL_VAL ; 
 int /*<<< orphan*/  BBPLL_OC_ENB_VCON_VAL ; 
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  I2C_BBPLL ; 
 int /*<<< orphan*/  I2C_BBPLL_BBADC_CAL_7_0 ; 
 int /*<<< orphan*/  I2C_BBPLL_IR_CAL_DELAY ; 
 int /*<<< orphan*/  I2C_BBPLL_IR_CAL_EXT_CAP ; 
 int /*<<< orphan*/  I2C_BBPLL_OC_ENB_FCAL ; 
 int /*<<< orphan*/  I2C_BBPLL_OC_ENB_VCON ; 
 int /*<<< orphan*/  I2C_WRITEREG_RTC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RTC_CNTL_BBPLL_FORCE_PD ; 
 int RTC_CNTL_BBPLL_I2C_FORCE_PD ; 
 int RTC_CNTL_BB_I2C_FORCE_PD ; 
 int RTC_CNTL_BIAS_I2C_FORCE_PD ; 
 int /*<<< orphan*/  RTC_CNTL_OPTIONS0_REG ; 

__attribute__((used)) static void rtc_clk_bbpll_enable(void)
{
    CLEAR_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG,
             RTC_CNTL_BIAS_I2C_FORCE_PD | RTC_CNTL_BB_I2C_FORCE_PD |
             RTC_CNTL_BBPLL_FORCE_PD | RTC_CNTL_BBPLL_I2C_FORCE_PD);

    /* reset BBPLL configuration */
    I2C_WRITEREG_RTC(I2C_BBPLL, I2C_BBPLL_IR_CAL_DELAY, BBPLL_IR_CAL_DELAY_VAL);
    I2C_WRITEREG_RTC(I2C_BBPLL, I2C_BBPLL_IR_CAL_EXT_CAP, BBPLL_IR_CAL_EXT_CAP_VAL);
    I2C_WRITEREG_RTC(I2C_BBPLL, I2C_BBPLL_OC_ENB_FCAL, BBPLL_OC_ENB_FCAL_VAL);
    I2C_WRITEREG_RTC(I2C_BBPLL, I2C_BBPLL_OC_ENB_VCON, BBPLL_OC_ENB_VCON_VAL);
    I2C_WRITEREG_RTC(I2C_BBPLL, I2C_BBPLL_BBADC_CAL_7_0, BBPLL_BBADC_CAL_7_0_VAL);
}