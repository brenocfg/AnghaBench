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
typedef  long long uint64_t ;
typedef  scalar_t__ const uint32_t ;
typedef  long long int64_t ;
typedef  long long const int32_t ;

/* Variables and functions */
 scalar_t__ const REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,scalar_t__ const) ; 
 long long RTC_CLK_CAL_FRACT ; 
 int /*<<< orphan*/  RTC_SLOW_CLK_CAL_REG ; 
 long long get_boot_time () ; 
 int /*<<< orphan*/  rtc_time_get () ; 
 int /*<<< orphan*/  set_boot_time (long long) ; 

void esp_clk_slowclk_cal_set(uint32_t new_cal)
{
#if defined(WITH_RTC)
    /* To force monotonic time values even when clock calibration value changes,
     * we adjust boot time, given current time and the new calibration value:
     *      T = boot_time_old + cur_cal * ticks / 2^19
     *      T = boot_time_adj + new_cal * ticks / 2^19
     * which results in:
     *      boot_time_adj = boot_time_old + ticks * (cur_cal - new_cal) / 2^19
     */
    const int64_t ticks = (int64_t) rtc_time_get();
    const uint32_t cur_cal = REG_READ(RTC_SLOW_CLK_CAL_REG);
    int32_t cal_diff = (int32_t) (cur_cal - new_cal);
    int64_t boot_time_diff = ticks * cal_diff / (1LL << RTC_CLK_CAL_FRACT);
    uint64_t boot_time_adj = get_boot_time() + boot_time_diff;
    set_boot_time(boot_time_adj);
#endif // WITH_RTC
    REG_WRITE(RTC_SLOW_CLK_CAL_REG, new_cal);
}