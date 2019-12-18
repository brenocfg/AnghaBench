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
struct TYPE_3__ {int timer_end; int timer_begin; scalar_t__ timeout_end; } ;
typedef  TYPE_1__ rarch_timer_t ;

/* Variables and functions */

void rarch_timer_end(rarch_timer_t *timer)
{
   if (!timer)
      return;
   timer->timer_end   = true;
   timer->timer_begin = false;
   timer->timeout_end = 0;
}