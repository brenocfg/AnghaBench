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
struct TYPE_3__ {scalar_t__ current; scalar_t__ timeout_end; scalar_t__ timeout_us; } ;
typedef  TYPE_1__ rarch_timer_t ;

/* Variables and functions */
 scalar_t__ cpu_features_get_time_usec () ; 

void rarch_timer_tick(rarch_timer_t *timer)
{
   if (!timer)
      return;
   timer->current = cpu_features_get_time_usec();
   timer->timeout_us = (timer->timeout_end - timer->current);
}