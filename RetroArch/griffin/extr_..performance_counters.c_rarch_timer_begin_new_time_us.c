#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {scalar_t__ timeout_us; scalar_t__ current; scalar_t__ timeout_end; } ;
typedef  TYPE_1__ rarch_timer_t ;

/* Variables and functions */
 scalar_t__ cpu_features_get_time_usec () ; 

void rarch_timer_begin_new_time_us(rarch_timer_t *timer, uint64_t usec)
{
   if (!timer)
      return;
   timer->timeout_us = usec;
   timer->current = cpu_features_get_time_usec();
   timer->timeout_end = timer->current + timer->timeout_us;
}