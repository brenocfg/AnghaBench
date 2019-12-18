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
typedef  int /*<<< orphan*/  rtc_cpu_freq_t ;

/* Variables and functions */
 int MAX (int,int) ; 
 int /*<<< orphan*/  RTC_CPU_FREQ_XTAL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_clk_cpu_freq_from_mhz (int,int /*<<< orphan*/ *) ; 
 int rtc_clk_cpu_freq_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtc_cpu_freq_t max_freq_of(rtc_cpu_freq_t f1, rtc_cpu_freq_t f2)
{
    int f1_hz = rtc_clk_cpu_freq_value(f1);
    int f2_hz = rtc_clk_cpu_freq_value(f2);
    int f_max_hz = MAX(f1_hz, f2_hz);
    rtc_cpu_freq_t result = RTC_CPU_FREQ_XTAL;
    if (!rtc_clk_cpu_freq_from_mhz(f_max_hz/1000000, &result)) {
        assert(false && "unsupported frequency");
    }
    return result;
}