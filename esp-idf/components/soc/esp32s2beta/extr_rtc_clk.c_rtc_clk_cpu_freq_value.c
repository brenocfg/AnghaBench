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
typedef  int uint32_t ;
typedef  int rtc_cpu_freq_t ;

/* Variables and functions */
 int MHZ ; 
#define  RTC_CPU_320M_160M 134 
#define  RTC_CPU_320M_80M 133 
#define  RTC_CPU_FREQ_160M 132 
#define  RTC_CPU_FREQ_240M 131 
#define  RTC_CPU_FREQ_2M 130 
#define  RTC_CPU_FREQ_80M 129 
#define  RTC_CPU_FREQ_XTAL 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_clk_xtal_freq_get () ; 

uint32_t rtc_clk_cpu_freq_value(rtc_cpu_freq_t cpu_freq)
{
    switch (cpu_freq) {
        case RTC_CPU_FREQ_XTAL:
            return ((uint32_t) rtc_clk_xtal_freq_get()) * MHZ;
        case RTC_CPU_FREQ_2M:
            return 2 * MHZ;
        case RTC_CPU_FREQ_80M:
            return 80 * MHZ;
        case RTC_CPU_FREQ_160M:
            return 160 * MHZ;
        case RTC_CPU_FREQ_240M:
            return 240 * MHZ;
        case RTC_CPU_320M_80M:
            return 80 * MHZ;
        case RTC_CPU_320M_160M:
            return 160 * MHZ;
        default:
            assert(false && "invalid rtc_cpu_freq_t value");
            return 0;
    }
}