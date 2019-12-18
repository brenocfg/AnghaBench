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
typedef  int /*<<< orphan*/  timer_handler_func ;
struct timeval {int tv_sec; int tv_usec; } ;
struct TYPE_4__ {int tv_sec; int tv_usec; } ;
struct gdb_timer {int timer_id; struct gdb_timer* next; TYPE_1__ when; int /*<<< orphan*/  client_data; int /*<<< orphan*/ * proc; } ;
typedef  int /*<<< orphan*/  gdb_timer ;
typedef  int /*<<< orphan*/  gdb_client_data ;
struct TYPE_6__ {scalar_t__ timeout_valid; } ;
struct TYPE_5__ {int num_timers; struct gdb_timer* first_timer; } ;

/* Variables and functions */
 TYPE_3__ gdb_notifier ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 TYPE_2__ timer_list ; 
 scalar_t__ xmalloc (int) ; 

int
create_timer (int milliseconds, timer_handler_func * proc, gdb_client_data client_data)
{
  struct gdb_timer *timer_ptr, *timer_index, *prev_timer;
  struct timeval time_now, delta;

  /* compute seconds */
  delta.tv_sec = milliseconds / 1000;
  /* compute microseconds */
  delta.tv_usec = (milliseconds % 1000) * 1000;

  gettimeofday (&time_now, NULL);

  timer_ptr = (struct gdb_timer *) xmalloc (sizeof (gdb_timer));
  timer_ptr->when.tv_sec = time_now.tv_sec + delta.tv_sec;
  timer_ptr->when.tv_usec = time_now.tv_usec + delta.tv_usec;
  /* carry? */
  if (timer_ptr->when.tv_usec >= 1000000)
    {
      timer_ptr->when.tv_sec += 1;
      timer_ptr->when.tv_usec -= 1000000;
    }
  timer_ptr->proc = proc;
  timer_ptr->client_data = client_data;
  timer_list.num_timers++;
  timer_ptr->timer_id = timer_list.num_timers;

  /* Now add the timer to the timer queue, making sure it is sorted in
     increasing order of expiration. */

  for (timer_index = timer_list.first_timer;
       timer_index != NULL;
       timer_index = timer_index->next)
    {
      /* If the seconds field is greater or if it is the same, but the
         microsecond field is greater. */
      if ((timer_index->when.tv_sec > timer_ptr->when.tv_sec) ||
	  ((timer_index->when.tv_sec == timer_ptr->when.tv_sec)
	   && (timer_index->when.tv_usec > timer_ptr->when.tv_usec)))
	break;
    }

  if (timer_index == timer_list.first_timer)
    {
      timer_ptr->next = timer_list.first_timer;
      timer_list.first_timer = timer_ptr;

    }
  else
    {
      for (prev_timer = timer_list.first_timer;
	   prev_timer->next != timer_index;
	   prev_timer = prev_timer->next)
	;

      prev_timer->next = timer_ptr;
      timer_ptr->next = timer_index;
    }

  gdb_notifier.timeout_valid = 0;
  return timer_ptr->timer_id;
}