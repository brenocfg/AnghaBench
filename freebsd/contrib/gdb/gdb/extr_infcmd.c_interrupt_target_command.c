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

/* Variables and functions */
 int /*<<< orphan*/  dont_repeat () ; 
 scalar_t__ event_loop_p ; 
 scalar_t__ target_can_async_p () ; 
 int /*<<< orphan*/  target_stop () ; 

void
interrupt_target_command (char *args, int from_tty)
{
  if (event_loop_p && target_can_async_p ())
    {
      dont_repeat ();		/* Not for the faint of heart */
      target_stop ();
    }
}