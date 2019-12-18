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
struct TYPE_3__ {int timer_begin; } ;
typedef  TYPE_1__ rarch_timer_t ;

/* Variables and functions */

bool rarch_timer_is_running(rarch_timer_t *timer)
{
   if (!timer)
      return false;
   return timer->timer_begin;
}