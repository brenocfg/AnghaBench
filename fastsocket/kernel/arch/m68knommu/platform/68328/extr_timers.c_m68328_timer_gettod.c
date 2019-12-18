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
 long RTCTIME ; 

void m68328_timer_gettod(int *year, int *mon, int *day, int *hour, int *min, int *sec)
{
	long now = RTCTIME;

	*year = *mon = *day = 1;
	*hour = (now >> 24) % 24;
	*min = (now >> 16) % 60;
	*sec = now % 60;
}