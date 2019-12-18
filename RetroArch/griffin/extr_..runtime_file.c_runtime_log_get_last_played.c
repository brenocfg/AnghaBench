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

void runtime_log_get_last_played(runtime_log_t *runtime_log,
      unsigned *year, unsigned *month, unsigned *day,
      unsigned *hour, unsigned *minute, unsigned *second)
{
   if (!runtime_log)
      return;
   
   *year   = runtime_log->last_played.year;
   *month  = runtime_log->last_played.month;
   *day    = runtime_log->last_played.day;
   *hour   = runtime_log->last_played.hour;
   *minute = runtime_log->last_played.minute;
   *second = runtime_log->last_played.second;
}