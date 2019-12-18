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
struct TYPE_4__ {unsigned int year; unsigned int month; unsigned int day; unsigned int hour; unsigned int minute; unsigned int second; } ;
struct TYPE_5__ {TYPE_1__ last_played; } ;
typedef  TYPE_2__ runtime_log_t ;

/* Variables and functions */

void runtime_log_set_last_played(runtime_log_t *runtime_log,
      unsigned year, unsigned month, unsigned day,
      unsigned hour, unsigned minute, unsigned second)
{
   if (!runtime_log)
      return;
   
   /* This function should never be needed, so just
    * perform dumb value assignment (i.e. no validation
    * using mktime()) */
   runtime_log->last_played.year   = year;
   runtime_log->last_played.month  = month;
   runtime_log->last_played.day    = day;
   runtime_log->last_played.hour   = hour;
   runtime_log->last_played.minute = minute;
   runtime_log->last_played.second = second;
}