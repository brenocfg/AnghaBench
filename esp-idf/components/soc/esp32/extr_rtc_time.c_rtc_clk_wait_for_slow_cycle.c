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
 int /*<<< orphan*/  GET_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_CLR_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_CAL_RTC_MUX ; 
 int /*<<< orphan*/  TIMG_RTCCALICFG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMG_RTC_CALI_CLK_SEL ; 
 int /*<<< orphan*/  TIMG_RTC_CALI_MAX ; 
 int TIMG_RTC_CALI_RDY ; 
 int TIMG_RTC_CALI_START ; 
 int TIMG_RTC_CALI_START_CYCLING ; 
 int /*<<< orphan*/  ets_delay_us (int) ; 

void rtc_clk_wait_for_slow_cycle(void)
{
    REG_CLR_BIT(TIMG_RTCCALICFG_REG(0), TIMG_RTC_CALI_START_CYCLING | TIMG_RTC_CALI_START);
    REG_CLR_BIT(TIMG_RTCCALICFG_REG(0), TIMG_RTC_CALI_RDY);
    REG_SET_FIELD(TIMG_RTCCALICFG_REG(0), TIMG_RTC_CALI_CLK_SEL, RTC_CAL_RTC_MUX);
    /* Request to run calibration for 0 slow clock cycles.
     * RDY bit will be set on the nearest slow clock cycle.
     */
    REG_SET_FIELD(TIMG_RTCCALICFG_REG(0), TIMG_RTC_CALI_MAX, 0);
    REG_SET_BIT(TIMG_RTCCALICFG_REG(0), TIMG_RTC_CALI_START);
    ets_delay_us(1); /* RDY needs some time to go low */
    while (!GET_PERI_REG_MASK(TIMG_RTCCALICFG_REG(0), TIMG_RTC_CALI_RDY)) {
        ets_delay_us(1);
    }
}