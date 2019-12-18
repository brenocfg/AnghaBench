#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct async_signal_handler {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mark_async_signal_handler (struct async_signal_handler*) ; 

void
mark_async_signal_handler_wrapper (void *token)
{
  mark_async_signal_handler ((struct async_signal_handler *) token);
}