#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int timer_begin; int timer_end; } ;
typedef  TYPE_1__ rarch_timer_t ;

/* Variables and functions */
 int /*<<< orphan*/  rarch_timer_begin_new_time_us (TYPE_1__*,int /*<<< orphan*/ ) ; 

void rarch_timer_begin_us(rarch_timer_t *timer, uint64_t usec)
{
   if (!timer)
      return;
   rarch_timer_begin_new_time_us(timer, usec);
   timer->timer_begin = true;
   timer->timer_end   = false;
}