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
 int /*<<< orphan*/  DIG_DBIAS_XTAL ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_CNTL_CLK_CONF_REG ; 
 int /*<<< orphan*/  RTC_CNTL_DIG_DBIAS_WAK ; 
 int /*<<< orphan*/  RTC_CNTL_REG ; 
 int /*<<< orphan*/  RTC_CNTL_SOC_CLK_SEL ; 
 int /*<<< orphan*/  RTC_CNTL_SOC_CLK_SEL_8M ; 
 int /*<<< orphan*/  RTC_FAST_CLK_FREQ_8M ; 
 int /*<<< orphan*/  ets_update_cpu_frequency (int) ; 
 int /*<<< orphan*/  rtc_clk_apb_freq_update (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtc_clk_cpu_freq_to_8m(void)
{
    ets_update_cpu_frequency(8);
    REG_SET_FIELD(RTC_CNTL_REG, RTC_CNTL_DIG_DBIAS_WAK, DIG_DBIAS_XTAL);
    REG_SET_FIELD(APB_CTRL_SYSCLK_CONF_REG, APB_CTRL_PRE_DIV_CNT, 0);
    REG_SET_FIELD(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_SOC_CLK_SEL, RTC_CNTL_SOC_CLK_SEL_8M);
    rtc_clk_apb_freq_update(RTC_FAST_CLK_FREQ_8M);
}