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
struct TYPE_3__ {int ready; } ;
typedef  TYPE_1__ async_signal_handler ;

/* Variables and functions */
 int async_handler_ready ; 

void
mark_async_signal_handler (async_signal_handler * async_handler_ptr)
{
  ((async_signal_handler *) async_handler_ptr)->ready = 1;
  async_handler_ready = 1;
}