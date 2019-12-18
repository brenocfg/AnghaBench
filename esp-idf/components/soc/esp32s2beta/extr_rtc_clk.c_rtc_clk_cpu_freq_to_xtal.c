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
typedef  int rtc_xtal_freq_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIG_DBIAS_XTAL ; 
 int MHZ ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_CNTL_DIG_DBIAS_WAK ; 
 int /*<<< orphan*/  RTC_CNTL_REG ; 
 int /*<<< orphan*/  RTC_CPU_FREQ_XTAL ; 
 int /*<<< orphan*/  RTC_PLL_NONE ; 
 int /*<<< orphan*/  SYSCON_PRE_DIV_CNT ; 
 int /*<<< orphan*/  SYSCON_SOC_CLK_SEL ; 
 int /*<<< orphan*/  SYSCON_SOC_CLK_SEL_XTL ; 
 int /*<<< orphan*/  SYSCON_SYSCLK_CONF_REG ; 
 int /*<<< orphan*/  ets_update_cpu_frequency (int) ; 
 int /*<<< orphan*/  rtc_clk_apb_freq_update (int) ; 
 int rtc_clk_xtal_freq_get () ; 
 int /*<<< orphan*/  s_cur_freq ; 
 int /*<<< orphan*/  s_cur_pll ; 

__attribute__((used)) static void rtc_clk_cpu_freq_to_xtal(void)
{
    rtc_xtal_freq_t xtal_freq = rtc_clk_xtal_freq_get();
    ets_update_cpu_frequency(xtal_freq);
    REG_SET_FIELD(RTC_CNTL_REG, RTC_CNTL_DIG_DBIAS_WAK, DIG_DBIAS_XTAL);
    REG_SET_FIELD(SYSCON_SYSCLK_CONF_REG, SYSCON_PRE_DIV_CNT, 0);
    REG_SET_FIELD(SYSCON_SYSCLK_CONF_REG, SYSCON_SOC_CLK_SEL, SYSCON_SOC_CLK_SEL_XTL);
    /* Why we need to do this ? */
    //DPORT_REG_WRITE(DPORT_CPU_PER_CONF_REG, 0); // clear DPORT_CPUPERIOD_SEL

    rtc_clk_apb_freq_update(xtal_freq * MHZ);
    s_cur_freq = RTC_CPU_FREQ_XTAL;
    s_cur_pll  = RTC_PLL_NONE;
}