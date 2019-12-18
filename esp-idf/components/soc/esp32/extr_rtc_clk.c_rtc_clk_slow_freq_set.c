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
 int /*<<< orphan*/  RTC_CNTL_CLK_CONF_REG ; 
 int /*<<< orphan*/  RTC_CNTL_DIG_XTAL32K_EN ; 
 scalar_t__ RTC_SLOW_FREQ_32K_XTAL ; 
 int /*<<< orphan*/  ets_delay_us (int /*<<< orphan*/ ) ; 

void rtc_clk_slow_freq_set(rtc_slow_freq_t slow_freq)
{
    REG_SET_FIELD(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_ANA_CLK_RTC_SEL, slow_freq);

    REG_SET_FIELD(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_DIG_XTAL32K_EN,
            (slow_freq == RTC_SLOW_FREQ_32K_XTAL) ? 1 : 0);

    ets_delay_us(DELAY_SLOW_CLK_SWITCH);
}