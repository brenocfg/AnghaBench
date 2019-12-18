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
struct tm {int tm_hour; int tm_min; int tm_sec; } ;

/* Variables and functions */
 int MAX_HOUR ; 
 int MAX_MINUTE ; 
 int MAX_SECOND ; 
 int /*<<< orphan*/  localtime_r (scalar_t__*,struct tm*) ; 
 scalar_t__ time (scalar_t__*) ; 

uint16_t _FAT_filetime_getTimeFromRTC (void)
{
#ifdef USE_RTC_TIME
   struct tm timeParts;
   time_t epochTime;

   if (time(&epochTime) == (time_t)-1)
      return 0;
   localtime_r(&epochTime, &timeParts);

   /* Check that the values are all in range.
    * If they are not, return 0 (no timestamp) */
   if ((timeParts.tm_hour < 0) || (timeParts.tm_hour > MAX_HOUR))
      return 0;
   if ((timeParts.tm_min < 0) || (timeParts.tm_min > MAX_MINUTE))
      return 0;
   if ((timeParts.tm_sec < 0) || (timeParts.tm_sec > MAX_SECOND))
      return 0;

   return (
         ((timeParts.tm_hour & 0x1F) << 11) |
         ((timeParts.tm_min & 0x3F) << 5) |
         ((timeParts.tm_sec >> 1) & 0x1F) 
         );
#else
   return 0;
#endif
}