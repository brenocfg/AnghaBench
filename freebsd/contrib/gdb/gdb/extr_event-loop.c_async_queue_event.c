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
typedef  scalar_t__ queue_position ;
struct TYPE_4__ {struct TYPE_4__* next_event; } ;
typedef  TYPE_1__ gdb_event ;
struct TYPE_5__ {TYPE_1__* first_event; TYPE_1__* last_event; } ;

/* Variables and functions */
 scalar_t__ HEAD ; 
 scalar_t__ TAIL ; 
 TYPE_2__ event_queue ; 

__attribute__((used)) static void
async_queue_event (gdb_event * event_ptr, queue_position position)
{
  if (position == TAIL)
    {
      /* The event will become the new last_event. */

      event_ptr->next_event = NULL;
      if (event_queue.first_event == NULL)
	event_queue.first_event = event_ptr;
      else
	event_queue.last_event->next_event = event_ptr;
      event_queue.last_event = event_ptr;
    }
  else if (position == HEAD)
    {
      /* The event becomes the new first_event. */

      event_ptr->next_event = event_queue.first_event;
      if (event_queue.first_event == NULL)
	event_queue.last_event = event_ptr;
      event_queue.first_event = event_ptr;
    }
}