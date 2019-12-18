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
struct TYPE_3__ {int /*<<< orphan*/  client_data; int /*<<< orphan*/  (* proc ) (int /*<<< orphan*/ ) ;scalar_t__ ready; struct TYPE_3__* next_handler; } ;
typedef  TYPE_1__ async_signal_handler ;
struct TYPE_4__ {TYPE_1__* first_handler; } ;

/* Variables and functions */
 scalar_t__ async_handler_ready ; 
 TYPE_2__ sighandler_list ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
invoke_async_signal_handler (void)
{
  async_signal_handler *async_handler_ptr;

  if (async_handler_ready == 0)
    return;
  async_handler_ready = 0;

  /* Invoke ready handlers. */

  while (1)
    {
      for (async_handler_ptr = sighandler_list.first_handler;
	   async_handler_ptr != NULL;
	   async_handler_ptr = async_handler_ptr->next_handler)
	{
	  if (async_handler_ptr->ready)
	    break;
	}
      if (async_handler_ptr == NULL)
	break;
      async_handler_ptr->ready = 0;
      (*async_handler_ptr->proc) (async_handler_ptr->client_data);
    }

  return;
}