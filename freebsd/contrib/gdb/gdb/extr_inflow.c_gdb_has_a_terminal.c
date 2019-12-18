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
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  TIOCGPGRP ; 
 int /*<<< orphan*/  fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gdb_has_a_terminal_flag ; 
 int /*<<< orphan*/  getpgrp () ; 
#define  have_not_checked 130 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  no 129 
 int /*<<< orphan*/  our_process_group ; 
 int /*<<< orphan*/ * our_ttystate ; 
 int /*<<< orphan*/ * serial_fdopen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * serial_get_tty_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stdin_serial ; 
 int /*<<< orphan*/  tcgetpgrp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tflags_ours ; 
#define  yes 128 

int
gdb_has_a_terminal (void)
{
  switch (gdb_has_a_terminal_flag)
    {
    case yes:
      return 1;
    case no:
      return 0;
    case have_not_checked:
      /* Get all the current tty settings (including whether we have a
         tty at all!).  Can't do this in _initialize_inflow because
         serial_fdopen() won't work until the serial_ops_list is
         initialized.  */

#ifdef F_GETFL
      tflags_ours = fcntl (0, F_GETFL, 0);
#endif

      gdb_has_a_terminal_flag = no;
      stdin_serial = serial_fdopen (0);
      if (stdin_serial != NULL)
	{
	  our_ttystate = serial_get_tty_state (stdin_serial);

	  if (our_ttystate != NULL)
	    {
	      gdb_has_a_terminal_flag = yes;
#ifdef HAVE_TERMIOS
	      our_process_group = tcgetpgrp (0);
#endif
#ifdef HAVE_TERMIO
	      our_process_group = getpgrp ();
#endif
#ifdef HAVE_SGTTY
	      ioctl (0, TIOCGPGRP, &our_process_group);
#endif
	    }
	}

      return gdb_has_a_terminal_flag == yes;
    default:
      /* "Can't happen".  */
      return 0;
    }
}