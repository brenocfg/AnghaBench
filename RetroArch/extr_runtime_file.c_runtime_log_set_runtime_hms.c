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
struct TYPE_4__ {int /*<<< orphan*/  seconds; int /*<<< orphan*/  minutes; int /*<<< orphan*/  hours; } ;
struct TYPE_5__ {TYPE_1__ runtime; } ;
typedef  TYPE_2__ runtime_log_t ;
typedef  int /*<<< orphan*/  retro_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  runtime_log_convert_hms2usec (unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  runtime_log_convert_usec2hms (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void runtime_log_set_runtime_hms(runtime_log_t *runtime_log, unsigned hours, unsigned minutes, unsigned seconds)
{
   retro_time_t usec;
   
   if (!runtime_log)
      return;
   
   /* Converting to usec and back again may be considered a
    * waste of CPU cycles, but this allows us to handle any
    * kind of broken input without issue - i.e. user can enter
    * minutes and seconds values > 59, and everything still
    * works correctly */
   runtime_log_convert_hms2usec(hours, minutes, seconds, &usec);
   
   runtime_log_convert_usec2hms(usec,
         &runtime_log->runtime.hours, &runtime_log->runtime.minutes, &runtime_log->runtime.seconds);
}