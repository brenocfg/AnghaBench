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
typedef  unsigned long time_t ;

/* Variables and functions */
 int set_rtc_mmss (unsigned long) ; 

int sh03_rtc_settimeofday(const time_t secs)
{
	unsigned long nowtime = secs;

	return set_rtc_mmss(nowtime);
}