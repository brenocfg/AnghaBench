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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ get_time_since_boot () ; 

uint32_t system_relative_time(uint32_t current_time)
{
#if defined( WITH_FRC ) || defined( WITH_RTC )
    return get_time_since_boot() - current_time;
#else
    return 0;
#endif
}