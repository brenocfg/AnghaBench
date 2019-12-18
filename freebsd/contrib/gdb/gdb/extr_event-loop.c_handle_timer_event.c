#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timeval {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_4__ {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct gdb_timer {int /*<<< orphan*/  client_data; int /*<<< orphan*/  (* proc ) (int /*<<< orphan*/ ) ;struct gdb_timer* next; TYPE_1__ when; } ;
struct TYPE_6__ {scalar_t__ timeout_valid; } ;
struct TYPE_5__ {struct gdb_timer* first_timer; } ;

/* Variables and functions */
 TYPE_3__ gdb_notifier ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 TYPE_2__ timer_list ; 
 int /*<<< orphan*/  xfree (struct gdb_timer*) ; 

__attribute__((used)) static void
handle_timer_event (int dummy)
{
  struct timeval time_now;
  struct gdb_timer *timer_ptr, *saved_timer;

  gettimeofday (&time_now, NULL);
  timer_ptr = timer_list.first_timer;

  while (timer_ptr != NULL)
    {
      if ((timer_ptr->when.tv_sec > time_now.tv_sec) ||
	  ((timer_ptr->when.tv_sec == time_now.tv_sec) &&
	   (timer_ptr->when.tv_usec > time_now.tv_usec)))
	break;

      /* Get rid of the timer from the beginning of the list. */
      timer_list.first_timer = timer_ptr->next;
      saved_timer = timer_ptr;
      timer_ptr = timer_ptr->next;
      /* Call the procedure associated with that timer. */
      (*saved_timer->proc) (saved_timer->client_data);
      xfree (saved_timer);
    }

  gdb_notifier.timeout_valid = 0;
}