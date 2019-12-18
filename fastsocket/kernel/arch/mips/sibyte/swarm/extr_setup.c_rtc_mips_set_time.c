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
#define  RTC_M4LT81 130 
#define  RTC_NONE 129 
#define  RTC_XICOR 128 
 int m41t81_set_time (unsigned long) ; 
 int swarm_rtc_type ; 
 int xicor_set_time (unsigned long) ; 

int rtc_mips_set_time(unsigned long sec)
{
	switch (swarm_rtc_type) {
	case RTC_XICOR:
		return xicor_set_time(sec);

	case RTC_M4LT81:
		return m41t81_set_time(sec);

	case RTC_NONE:
	default:
		return -1;
	}
}