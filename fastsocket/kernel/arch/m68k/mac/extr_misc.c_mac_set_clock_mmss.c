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
struct rtc_time {unsigned long tm_sec; unsigned long tm_min; } ;

/* Variables and functions */
 int /*<<< orphan*/  mac_hwclk (int,struct rtc_time*) ; 

int mac_set_clock_mmss (unsigned long nowtime)
{
	struct rtc_time now;

	mac_hwclk(0, &now);
	now.tm_sec = nowtime % 60;
	now.tm_min = (nowtime / 60) % 60;
	mac_hwclk(1, &now);

	return 0;
}