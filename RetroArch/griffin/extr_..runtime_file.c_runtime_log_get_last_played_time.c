#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; int tm_isdst; } ;
struct TYPE_4__ {scalar_t__ second; scalar_t__ minute; scalar_t__ hour; scalar_t__ day; scalar_t__ month; scalar_t__ year; } ;
struct TYPE_5__ {TYPE_1__ last_played; } ;
typedef  TYPE_2__ runtime_log_t ;

/* Variables and functions */
 int /*<<< orphan*/  mktime (struct tm*) ; 

void runtime_log_get_last_played_time(runtime_log_t *runtime_log, struct tm *time_info)
{
   if (!runtime_log || !time_info)
      return;
   
   /* Set tm values */
   time_info->tm_year  = (int)runtime_log->last_played.year  - 1900;
   time_info->tm_mon   = (int)runtime_log->last_played.month - 1;
   time_info->tm_mday  = (int)runtime_log->last_played.day;
   time_info->tm_hour  = (int)runtime_log->last_played.hour;
   time_info->tm_min   = (int)runtime_log->last_played.minute;
   time_info->tm_sec   = (int)runtime_log->last_played.second;
   time_info->tm_isdst = -1;
   
   /* Perform any required range adjustment + populate
    * missing entries */
   mktime(time_info);
}