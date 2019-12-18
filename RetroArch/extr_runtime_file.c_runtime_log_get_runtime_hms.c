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
struct TYPE_4__ {unsigned int hours; unsigned int minutes; unsigned int seconds; } ;
struct TYPE_5__ {TYPE_1__ runtime; } ;
typedef  TYPE_2__ runtime_log_t ;

/* Variables and functions */

void runtime_log_get_runtime_hms(runtime_log_t *runtime_log,
      unsigned *hours, unsigned *minutes, unsigned *seconds)
{
   if (!runtime_log)
      return;
   
   *hours   = runtime_log->runtime.hours;
   *minutes = runtime_log->runtime.minutes;
   *seconds = runtime_log->runtime.seconds;
}