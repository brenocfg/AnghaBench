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
struct rtc_time {int dummy; } ;

/* Variables and functions */
 unsigned long RCNR ; 
 unsigned long RTAR ; 
 int RTSR ; 
 int RTSR_AL ; 
 int RTSR_ALE ; 
 int RTSR_HZE ; 
 int /*<<< orphan*/  rtc_next_alarm_time (struct rtc_time*,struct rtc_time*,struct rtc_time*) ; 
 int /*<<< orphan*/  rtc_time_to_tm (unsigned long,struct rtc_time*) ; 
 int rtc_tm_to_time (struct rtc_time*,unsigned long*) ; 

__attribute__((used)) static int rtc_update_alarm(struct rtc_time *alrm)
{
	struct rtc_time alarm_tm, now_tm;
	unsigned long now, time;
	int ret;

	do {
		now = RCNR;
		rtc_time_to_tm(now, &now_tm);
		rtc_next_alarm_time(&alarm_tm, &now_tm, alrm);
		ret = rtc_tm_to_time(&alarm_tm, &time);
		if (ret != 0)
			break;

		RTSR = RTSR & (RTSR_HZE|RTSR_ALE|RTSR_AL);
		RTAR = time;
	} while (now != RCNR);

	return ret;
}