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
typedef  int /*<<< orphan*/  rtc_fast_freq_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY_FAST_CLK_SWITCH ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_CNTL_CLK_CONF_REG ; 
 int /*<<< orphan*/  RTC_CNTL_FAST_CLK_RTC_SEL ; 
 int /*<<< orphan*/  ets_delay_us (int /*<<< orphan*/ ) ; 

void rtc_clk_fast_freq_set(rtc_fast_freq_t fast_freq)
{
    REG_SET_FIELD(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_FAST_CLK_RTC_SEL, fast_freq);
    ets_delay_us(DELAY_FAST_CLK_SWITCH);
}