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
 int /*<<< orphan*/  aica_rtc_gettimeofday ; 
 int /*<<< orphan*/  aica_rtc_settimeofday ; 
 int /*<<< orphan*/  rtc_sh_get_time ; 
 int /*<<< orphan*/  rtc_sh_set_time ; 

void aica_time_init(void)
{
	rtc_sh_get_time = aica_rtc_gettimeofday;
	rtc_sh_set_time = aica_rtc_settimeofday;
}