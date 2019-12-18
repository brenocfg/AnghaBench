#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gdb_timer {int timer_id; struct gdb_timer* next; } ;
struct TYPE_4__ {scalar_t__ timeout_valid; } ;
struct TYPE_3__ {struct gdb_timer* first_timer; } ;

/* Variables and functions */
 TYPE_2__ gdb_notifier ; 
 TYPE_1__ timer_list ; 
 int /*<<< orphan*/  xfree (struct gdb_timer*) ; 

void
delete_timer (int id)
{
  struct gdb_timer *timer_ptr, *prev_timer = NULL;

  /* Find the entry for the given timer. */

  for (timer_ptr = timer_list.first_timer; timer_ptr != NULL;
       timer_ptr = timer_ptr->next)
    {
      if (timer_ptr->timer_id == id)
	break;
    }

  if (timer_ptr == NULL)
    return;
  /* Get rid of the timer in the timer list. */
  if (timer_ptr == timer_list.first_timer)
    timer_list.first_timer = timer_ptr->next;
  else
    {
      for (prev_timer = timer_list.first_timer;
	   prev_timer->next != timer_ptr;
	   prev_timer = prev_timer->next)
	;
      prev_timer->next = timer_ptr->next;
    }
  xfree (timer_ptr);

  gdb_notifier.timeout_valid = 0;
}