#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  rtc_xtal_freq_t ;
struct TYPE_3__ {scalar_t__ source; int div; int /*<<< orphan*/  freq_mhz; int /*<<< orphan*/  source_freq_mhz; } ;
typedef  TYPE_1__ rtc_cpu_freq_config_t ;

/* Variables and functions */
 scalar_t__ REG_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_CNTL_CLK_CONF_REG ; 
 int /*<<< orphan*/  RTC_CNTL_SOC_CLK_SEL ; 
 scalar_t__ RTC_CNTL_SOC_CLK_SEL_PLL ; 
 scalar_t__ RTC_CNTL_SOC_CLK_SEL_XTL ; 
 scalar_t__ RTC_CPU_FREQ_SRC_8M ; 
 scalar_t__ RTC_CPU_FREQ_SRC_PLL ; 
 scalar_t__ RTC_CPU_FREQ_SRC_XTAL ; 
 int /*<<< orphan*/  rtc_clk_bbpll_configure (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_clk_bbpll_disable () ; 
 int /*<<< orphan*/  rtc_clk_bbpll_enable () ; 
 int /*<<< orphan*/  rtc_clk_cpu_freq_to_8m () ; 
 int /*<<< orphan*/  rtc_clk_cpu_freq_to_pll_mhz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_clk_cpu_freq_to_xtal (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtc_clk_wait_for_slow_cycle () ; 
 int /*<<< orphan*/  rtc_clk_xtal_freq_get () ; 

void rtc_clk_cpu_freq_set_config(const rtc_cpu_freq_config_t* config)
{
    rtc_xtal_freq_t xtal_freq = rtc_clk_xtal_freq_get();
    uint32_t soc_clk_sel = REG_GET_FIELD(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_SOC_CLK_SEL);
    if (soc_clk_sel != RTC_CNTL_SOC_CLK_SEL_XTL) {
        rtc_clk_cpu_freq_to_xtal(xtal_freq, 1);
        rtc_clk_wait_for_slow_cycle();
    }
    if (soc_clk_sel == RTC_CNTL_SOC_CLK_SEL_PLL) {
        rtc_clk_bbpll_disable();
    }
    if (config->source == RTC_CPU_FREQ_SRC_XTAL) {
        if (config->div > 1) {
            rtc_clk_cpu_freq_to_xtal(config->freq_mhz, config->div);
        }
    } else if (config->source == RTC_CPU_FREQ_SRC_PLL) {
        rtc_clk_bbpll_enable();
        rtc_clk_wait_for_slow_cycle();
        rtc_clk_bbpll_configure(rtc_clk_xtal_freq_get(), config->source_freq_mhz);
        rtc_clk_cpu_freq_to_pll_mhz(config->freq_mhz);
    } else if (config->source == RTC_CPU_FREQ_SRC_8M) {
        rtc_clk_cpu_freq_to_8m();
    }
}