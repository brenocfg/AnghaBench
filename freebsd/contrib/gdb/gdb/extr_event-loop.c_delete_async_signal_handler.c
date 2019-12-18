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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next_handler; } ;
typedef  TYPE_1__ async_signal_handler ;
struct TYPE_6__ {TYPE_1__* last_handler; TYPE_1__* first_handler; } ;

/* Variables and functions */
 TYPE_3__ sighandler_list ; 
 int /*<<< orphan*/  xfree (TYPE_1__*) ; 

void
delete_async_signal_handler (async_signal_handler ** async_handler_ptr)
{
  async_signal_handler *prev_ptr;

  if (sighandler_list.first_handler == (*async_handler_ptr))
    {
      sighandler_list.first_handler = (*async_handler_ptr)->next_handler;
      if (sighandler_list.first_handler == NULL)
	sighandler_list.last_handler = NULL;
    }
  else
    {
      prev_ptr = sighandler_list.first_handler;
      while (prev_ptr->next_handler != (*async_handler_ptr) && prev_ptr)
	prev_ptr = prev_ptr->next_handler;
      prev_ptr->next_handler = (*async_handler_ptr)->next_handler;
      if (sighandler_list.last_handler == (*async_handler_ptr))
	sighandler_list.last_handler = prev_ptr;
    }
  xfree ((*async_handler_ptr));
  (*async_handler_ptr) = NULL;
}