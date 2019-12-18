#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ source; scalar_t__ source_freq_mhz; int /*<<< orphan*/  freq_mhz; int /*<<< orphan*/  div; } ;
typedef  TYPE_1__ rtc_cpu_freq_config_t ;

/* Variables and functions */
 scalar_t__ RTC_CPU_FREQ_SRC_PLL ; 
 scalar_t__ RTC_CPU_FREQ_SRC_XTAL ; 
 int /*<<< orphan*/  rtc_clk_cpu_freq_set_config (TYPE_1__ const*) ; 
 int /*<<< orphan*/  rtc_clk_cpu_freq_to_pll_mhz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_clk_cpu_freq_to_xtal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ s_cur_pll_freq ; 

void rtc_clk_cpu_freq_set_config_fast(const rtc_cpu_freq_config_t* config)
{
    if (config->source == RTC_CPU_FREQ_SRC_XTAL) {
        rtc_clk_cpu_freq_to_xtal(config->freq_mhz, config->div);
    } else if (config->source == RTC_CPU_FREQ_SRC_PLL &&
            s_cur_pll_freq == config->source_freq_mhz) {
        rtc_clk_cpu_freq_to_pll_mhz(config->freq_mhz);
    } else {
        /* fallback */
        rtc_clk_cpu_freq_set_config(config);
    }
}