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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int RTC_CLK_CAL_FRACT ; 

uint64_t rtc_time_us_to_slowclk(uint64_t time_in_us, uint32_t period)
{
    /* Overflow will happen in this function if time_in_us >= 2^45, which is about 400 days.
     * TODO: fix overflow.
     */
    return (time_in_us << RTC_CLK_CAL_FRACT) / period;
}