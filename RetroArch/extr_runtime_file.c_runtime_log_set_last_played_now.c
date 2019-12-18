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
typedef  int /*<<< orphan*/  time_t ;
struct tm {scalar_t__ tm_sec; scalar_t__ tm_min; scalar_t__ tm_hour; scalar_t__ tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
struct TYPE_4__ {unsigned int year; unsigned int month; unsigned int day; unsigned int hour; unsigned int minute; unsigned int second; } ;
struct TYPE_5__ {TYPE_1__ last_played; } ;
typedef  TYPE_2__ runtime_log_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void runtime_log_set_last_played_now(runtime_log_t *runtime_log)
{
   time_t current_time;
   struct tm *time_info;
   
   if (!runtime_log)
      return;
   
   /* Get current time */
   time(&current_time);
   time_info = localtime(&current_time);
   
   /* This can actually happen, but if does we probably
    * have bigger problems to worry about... */
   if(!time_info)
   {
      RARCH_ERR("Failed to get current time.\n");
      return;
   }
   
   /* Extract values */
   runtime_log->last_played.year   = (unsigned)time_info->tm_year + 1900;
   runtime_log->last_played.month  = (unsigned)time_info->tm_mon + 1;
   runtime_log->last_played.day    = (unsigned)time_info->tm_mday;
   runtime_log->last_played.hour   = (unsigned)time_info->tm_hour;
   runtime_log->last_played.minute = (unsigned)time_info->tm_min;
   runtime_log->last_played.second = (unsigned)time_info->tm_sec;
}