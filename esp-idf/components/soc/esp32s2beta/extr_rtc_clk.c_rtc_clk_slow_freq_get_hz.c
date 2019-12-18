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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_SLOW_CLK_FREQ_32K ; 
 int /*<<< orphan*/  RTC_SLOW_CLK_FREQ_8MD256 ; 
 int /*<<< orphan*/  RTC_SLOW_CLK_FREQ_90K ; 
#define  RTC_SLOW_FREQ_32K_XTAL 130 
#define  RTC_SLOW_FREQ_8MD256 129 
#define  RTC_SLOW_FREQ_RTC 128 
 int rtc_clk_slow_freq_get () ; 

uint32_t rtc_clk_slow_freq_get_hz(void)
{
    switch(rtc_clk_slow_freq_get()) {
        case RTC_SLOW_FREQ_RTC: return RTC_SLOW_CLK_FREQ_90K;
        case RTC_SLOW_FREQ_32K_XTAL: return RTC_SLOW_CLK_FREQ_32K;
        case RTC_SLOW_FREQ_8MD256: return RTC_SLOW_CLK_FREQ_8MD256;
    }
    return 0;
}