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
 int /*<<< orphan*/  rtc_clk_bbpll_disable () ; 
 int /*<<< orphan*/  rtc_clk_cpu_freq_to_xtal (int,int) ; 
 int /*<<< orphan*/  rtc_clk_wait_for_slow_cycle () ; 
 scalar_t__ rtc_clk_xtal_freq_get () ; 

void rtc_clk_cpu_freq_set_xtal(void)
{
    int freq_mhz = (int) rtc_clk_xtal_freq_get();

    rtc_clk_cpu_freq_to_xtal(freq_mhz, 1);
    rtc_clk_wait_for_slow_cycle();
    rtc_clk_bbpll_disable();
}