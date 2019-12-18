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
typedef  scalar_t__ rtc_slow_freq_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY_SLOW_CLK_SWITCH ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTC_CNTL_ANA_CLK_RTC_SEL ; 
 int /*<<< orphan*/  RTC_CNTL_CK8M_FORCE_PU ; 
 int /*<<< orphan*/  RTC_CNTL_CLK_CONF_REG ; 
 int /*<<< orphan*/  RTC_CNTL_DIG_XTAL32K_EN ; 
 scalar_t__ RTC_SLOW_FREQ_32K_XTAL ; 
 scalar_t__ RTC_SLOW_FREQ_8MD256 ; 
 int /*<<< orphan*/  ets_delay_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_clk_set_xtal_wait () ; 

void rtc_clk_slow_freq_set(rtc_slow_freq_t slow_freq)
{
    REG_SET_FIELD(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_ANA_CLK_RTC_SEL, slow_freq);

    /* Why we need to connect this clock to digital?
     * Or maybe this clock should be connected to digital when xtal 32k clock is enabled instead?
     */
    REG_SET_FIELD(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_DIG_XTAL32K_EN,
            (slow_freq == RTC_SLOW_FREQ_32K_XTAL) ? 1 : 0);

    /* The clk_8m_d256 will be closed when rtc_state in SLEEP,
    so if the slow_clk is 8md256, clk_8m must be force power on
    */
    REG_SET_FIELD(RTC_CNTL_CLK_CONF_REG,RTC_CNTL_CK8M_FORCE_PU, (slow_freq == RTC_SLOW_FREQ_8MD256) ? 1 : 0);
    rtc_clk_set_xtal_wait();
    ets_delay_us(DELAY_SLOW_CLK_SWITCH);
}