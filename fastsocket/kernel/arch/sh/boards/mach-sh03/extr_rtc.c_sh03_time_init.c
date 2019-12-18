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
 int /*<<< orphan*/  rtc_sh_get_time ; 
 int /*<<< orphan*/  rtc_sh_set_time ; 
 int /*<<< orphan*/  sh03_rtc_gettimeofday ; 
 int /*<<< orphan*/  sh03_rtc_settimeofday ; 

void sh03_time_init(void)
{
	rtc_sh_get_time = sh03_rtc_gettimeofday;
	rtc_sh_set_time = sh03_rtc_settimeofday;
}