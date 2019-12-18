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
typedef  int /*<<< orphan*/  sig_handler_func ;
typedef  int /*<<< orphan*/  gdb_client_data ;
struct TYPE_4__ {struct TYPE_4__* next_handler; int /*<<< orphan*/  client_data; int /*<<< orphan*/ * proc; scalar_t__ ready; } ;
typedef  TYPE_1__ async_signal_handler ;
struct TYPE_5__ {TYPE_1__* last_handler; TYPE_1__* first_handler; } ;

/* Variables and functions */
 TYPE_2__ sighandler_list ; 
 scalar_t__ xmalloc (int) ; 

async_signal_handler *
create_async_signal_handler (sig_handler_func * proc, gdb_client_data client_data)
{
  async_signal_handler *async_handler_ptr;

  async_handler_ptr =
    (async_signal_handler *) xmalloc (sizeof (async_signal_handler));
  async_handler_ptr->ready = 0;
  async_handler_ptr->next_handler = NULL;
  async_handler_ptr->proc = proc;
  async_handler_ptr->client_data = client_data;
  if (sighandler_list.first_handler == NULL)
    sighandler_list.first_handler = async_handler_ptr;
  else
    sighandler_list.last_handler->next_handler = async_handler_ptr;
  sighandler_list.last_handler = async_handler_ptr;
  return async_handler_ptr;
}