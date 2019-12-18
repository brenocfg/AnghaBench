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
 scalar_t__ gdb_has_a_terminal () ; 
 scalar_t__ our_ttystate ; 
 scalar_t__ serial_get_tty_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin_serial ; 
 int /*<<< orphan*/  xfree (scalar_t__) ; 

void
terminal_save_ours (void)
{
  if (gdb_has_a_terminal ())
    {
      /* We could just as well copy our_ttystate (if we felt like adding
         a new function serial_copy_tty_state).  */
      if (our_ttystate)
        xfree (our_ttystate);
      our_ttystate = serial_get_tty_state (stdin_serial);
    }
}