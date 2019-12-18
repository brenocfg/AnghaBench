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
 int inferior_process_group ; 
 scalar_t__ inferior_ttystate ; 
 scalar_t__ serial_get_tty_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin_serial ; 
 int terminal_is_ours ; 
 int /*<<< orphan*/  xfree (scalar_t__) ; 

void
terminal_init_inferior_with_pgrp (int pgrp)
{
  if (gdb_has_a_terminal ())
    {
      /* We could just as well copy our_ttystate (if we felt like
         adding a new function serial_copy_tty_state()).  */
      if (inferior_ttystate)
	xfree (inferior_ttystate);
      inferior_ttystate = serial_get_tty_state (stdin_serial);

#ifdef PROCESS_GROUP_TYPE
      inferior_process_group = pgrp;
#endif

      /* Make sure that next time we call terminal_inferior (which will be
         before the program runs, as it needs to be), we install the new
         process group.  */
      terminal_is_ours = 1;
    }
}