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
struct timespec {unsigned long tv_sec; scalar_t__ tv_nsec; } ;

/* Variables and functions */
#define  RTC_M4LT81 130 
#define  RTC_NONE 129 
#define  RTC_XICOR 128 
 unsigned long m41t81_get_time () ; 
 unsigned long mktime (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int swarm_rtc_type ; 
 unsigned long xicor_get_time () ; 

void read_persistent_clock(struct timespec *ts)
{
	unsigned long sec;

	switch (swarm_rtc_type) {
	case RTC_XICOR:
		sec = xicor_get_time();
		break;

	case RTC_M4LT81:
		sec = m41t81_get_time();
		break;

	case RTC_NONE:
	default:
		sec = mktime(2000, 1, 1, 0, 0, 0);
		break;
	}
	ts->tv_sec = sec;
	ts->tv_nsec = 0;
}