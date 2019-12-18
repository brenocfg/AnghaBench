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
 int /*<<< orphan*/  APB_CTRL_PRE_DIV_CNT ; 
 int /*<<< orphan*/  APB_CTRL_SYSCLK_CONF_REG ; 
 int /*<<< orphan*/  APB_CTRL_XTAL_TICK_CONF_REG ; 
 int DIG_DBIAS_2M ; 
 int DIG_DBIAS_XTAL ; 
 int MHZ ; 
 int REF_CLK_FREQ ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTC_CNTL_CLK_CONF_REG ; 
 int /*<<< orphan*/  RTC_CNTL_DIG_DBIAS_WAK ; 
 int /*<<< orphan*/  RTC_CNTL_REG ; 
 int /*<<< orphan*/  RTC_CNTL_SOC_CLK_SEL ; 
 int RTC_CNTL_SOC_CLK_SEL_XTL ; 
 int /*<<< orphan*/  ets_update_cpu_frequency (int) ; 
 int /*<<< orphan*/  rtc_clk_apb_freq_update (int) ; 

void rtc_clk_cpu_freq_to_xtal(int freq, int div)
{
    ets_update_cpu_frequency(freq);
    /* set divider from XTAL to APB clock */
    REG_SET_FIELD(APB_CTRL_SYSCLK_CONF_REG, APB_CTRL_PRE_DIV_CNT, div - 1);
    /* adjust ref_tick */
    REG_WRITE(APB_CTRL_XTAL_TICK_CONF_REG, freq * MHZ / REF_CLK_FREQ - 1);
    /* switch clock source */
    REG_SET_FIELD(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_SOC_CLK_SEL, RTC_CNTL_SOC_CLK_SEL_XTL);
    rtc_clk_apb_freq_update(freq * MHZ);
    /* lower the voltage */
    if (freq <= 2) {
        REG_SET_FIELD(RTC_CNTL_REG, RTC_CNTL_DIG_DBIAS_WAK, DIG_DBIAS_2M);
    } else {
        REG_SET_FIELD(RTC_CNTL_REG, RTC_CNTL_DIG_DBIAS_WAK, DIG_DBIAS_XTAL);
    }
}