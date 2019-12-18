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
typedef  int uint16_t ;
typedef  scalar_t__ time_t ;
struct tm {int tm_mon; int tm_mday; int tm_year; } ;

/* Variables and functions */
 int MAX_DAY ; 
 int MAX_MONTH ; 
 int MIN_DAY ; 
 int MIN_MONTH ; 
 int /*<<< orphan*/  localtime_r (scalar_t__*,struct tm*) ; 
 scalar_t__ time (scalar_t__*) ; 

uint16_t _FAT_filetime_getDateFromRTC (void) {
#ifdef USE_RTC_TIME
	struct tm timeParts;
	time_t epochTime;

	if (time(&epochTime) == (time_t)-1) {
		return 0;
	}
	localtime_r(&epochTime, &timeParts);

	if ((timeParts.tm_mon < MIN_MONTH) || (timeParts.tm_mon > MAX_MONTH)) return 0;
	if ((timeParts.tm_mday < MIN_DAY) || (timeParts.tm_mday > MAX_DAY)) return 0;

	return (
		(((timeParts.tm_year - 80) & 0x7F) <<9) |	// Adjust for MS-FAT base year (1980 vs 1900 for tm_year)
		(((timeParts.tm_mon + 1) & 0xF) << 5) |
		(timeParts.tm_mday & 0x1F)
	);
#else
	return 0;
#endif
}