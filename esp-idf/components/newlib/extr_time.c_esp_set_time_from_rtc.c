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
 scalar_t__ esp_timer_get_time () ; 
 scalar_t__ get_rtc_time_us () ; 
 scalar_t__ s_microseconds_offset ; 

void esp_set_time_from_rtc(void)
{
#if defined( WITH_FRC ) && defined( WITH_RTC )
    // initialize time from RTC clock
    s_microseconds_offset = get_rtc_time_us() - esp_timer_get_time();
#endif // WITH_FRC && WITH_RTC
}