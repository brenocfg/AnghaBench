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
struct TYPE_4__ {scalar_t__ hours; scalar_t__ minutes; scalar_t__ seconds; } ;
struct TYPE_5__ {TYPE_1__ runtime; } ;
typedef  TYPE_2__ runtime_log_t ;

/* Variables and functions */

bool runtime_log_has_runtime(runtime_log_t *runtime_log)
{
   if (!runtime_log)
      return false;
   
   return !((runtime_log->runtime.hours   == 0) &&
            (runtime_log->runtime.minutes == 0) &&
            (runtime_log->runtime.seconds == 0));
}