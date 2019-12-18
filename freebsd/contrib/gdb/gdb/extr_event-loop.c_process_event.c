#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int fd; struct TYPE_4__* next_event; int /*<<< orphan*/  (* proc ) (int) ;} ;
typedef  TYPE_1__ gdb_event ;
typedef  int /*<<< orphan*/  (* event_handler_func ) (int) ;
struct TYPE_5__ {TYPE_1__* last_event; TYPE_1__* first_event; } ;

/* Variables and functions */
 scalar_t__ check_async_ready () ; 
 TYPE_3__ event_queue ; 
 int /*<<< orphan*/  invoke_async_signal_handler () ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  xfree (TYPE_1__*) ; 

__attribute__((used)) static int
process_event (void)
{
  gdb_event *event_ptr, *prev_ptr;
  event_handler_func *proc;
  int fd;

  /* First let's see if there are any asynchronous event handlers that
     are ready. These would be the result of invoking any of the
     signal handlers. */

  if (check_async_ready ())
    {
      invoke_async_signal_handler ();
      return 1;
    }

  /* Look in the event queue to find an event that is ready
     to be processed. */

  for (event_ptr = event_queue.first_event; event_ptr != NULL;
       event_ptr = event_ptr->next_event)
    {
      /* Call the handler for the event. */

      proc = event_ptr->proc;
      fd = event_ptr->fd;

      /* Let's get rid of the event from the event queue.  We need to
         do this now because while processing the event, the proc
         function could end up calling 'error' and therefore jump out
         to the caller of this function, gdb_do_one_event. In that
         case, we would have on the event queue an event wich has been
         processed, but not deleted. */

      if (event_queue.first_event == event_ptr)
	{
	  event_queue.first_event = event_ptr->next_event;
	  if (event_ptr->next_event == NULL)
	    event_queue.last_event = NULL;
	}
      else
	{
	  prev_ptr = event_queue.first_event;
	  while (prev_ptr->next_event != event_ptr)
	    prev_ptr = prev_ptr->next_event;

	  prev_ptr->next_event = event_ptr->next_event;
	  if (event_ptr->next_event == NULL)
	    event_queue.last_event = prev_ptr;
	}
      xfree (event_ptr);

      /* Now call the procedure associated with the event. */
      (*proc) (fd);
      return 1;
    }

  /* this is the case if there are no event on the event queue. */
  return 0;
}