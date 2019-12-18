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
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTTOU ; 
 void SIG_IGN () ; 
 int /*<<< orphan*/  TIOCGPGRP ; 
 int /*<<< orphan*/  TIOCSPGRP ; 
 int /*<<< orphan*/  errno ; 
 void* fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ gdb_has_a_terminal () ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  getpgrp () ; 
 int /*<<< orphan*/  inferior_process_group ; 
 scalar_t__ inferior_thisrun_terminal ; 
 scalar_t__ inferior_ttystate ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ job_control ; 
 int /*<<< orphan*/  our_process_group ; 
 int /*<<< orphan*/  our_ttystate ; 
 int /*<<< orphan*/  safe_strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ serial_get_tty_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_noflush_set_tty_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 void sigint_ours () ; 
 scalar_t__ signal (int /*<<< orphan*/ ,void (*) ()) ; 
 void sigquit_ours () ; 
 int /*<<< orphan*/  stdin_serial ; 
 int /*<<< orphan*/  tcgetpgrp (int /*<<< orphan*/ ) ; 
 int tcsetpgrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int terminal_is_ours ; 
 void* tflags_inferior ; 
 int /*<<< orphan*/  tflags_ours ; 
 int /*<<< orphan*/  xfree (scalar_t__) ; 

__attribute__((used)) static void
terminal_ours_1 (int output_only)
{
  /* Checking inferior_thisrun_terminal is necessary so that
     if GDB is running in the background, it won't block trying
     to do the ioctl()'s below.  Checking gdb_has_a_terminal
     avoids attempting all the ioctl's when running in batch.  */
  if (inferior_thisrun_terminal != 0 || gdb_has_a_terminal () == 0)
    return;

  if (!terminal_is_ours)
    {
#ifdef SIGTTOU
      /* Ignore this signal since it will happen when we try to set the
         pgrp.  */
      void (*osigttou) () = NULL;
#endif
      int result;

      terminal_is_ours = 1;

#ifdef SIGTTOU
      if (job_control)
	osigttou = (void (*)()) signal (SIGTTOU, SIG_IGN);
#endif

      if (inferior_ttystate)
	xfree (inferior_ttystate);
      inferior_ttystate = serial_get_tty_state (stdin_serial);
#ifdef HAVE_TERMIOS
      inferior_process_group = tcgetpgrp (0);
#endif
#ifdef HAVE_TERMIO
      inferior_process_group = getpgrp ();
#endif
#ifdef HAVE_SGTTY
      ioctl (0, TIOCGPGRP, &inferior_process_group);
#endif

      /* Here we used to set ICANON in our ttystate, but I believe this
         was an artifact from before when we used readline.  Readline sets
         the tty state when it needs to.
         FIXME-maybe: However, query() expects non-raw mode and doesn't
         use readline.  Maybe query should use readline (on the other hand,
         this only matters for HAVE_SGTTY, not termio or termios, I think).  */

      /* Set tty state to our_ttystate.  We don't change in our out of raw
         mode, to avoid flushing input.  We need to do the same thing
         regardless of output_only, because we don't have separate
         terminal_is_ours and terminal_is_ours_for_output flags.  It's OK,
         though, since readline will deal with raw mode when/if it needs to.
       */

      serial_noflush_set_tty_state (stdin_serial, our_ttystate,
				    inferior_ttystate);

      if (job_control)
	{
#ifdef HAVE_TERMIOS
	  result = tcsetpgrp (0, our_process_group);
#if 0
	  /* This fails on Ultrix with EINVAL if you run the testsuite
	     in the background with nohup, and then log out.  GDB never
	     used to check for an error here, so perhaps there are other
	     such situations as well.  */
	  if (result == -1)
	    fprintf_unfiltered (gdb_stderr, "[tcsetpgrp failed in terminal_ours: %s]\n",
				safe_strerror (errno));
#endif
#endif /* termios */

#ifdef HAVE_SGTTY
	  result = ioctl (0, TIOCSPGRP, &our_process_group);
#endif
	}

#ifdef SIGTTOU
      if (job_control)
	signal (SIGTTOU, osigttou);
#endif

      if (!job_control)
	{
	  signal (SIGINT, sigint_ours);
#ifdef SIGQUIT
	  signal (SIGQUIT, sigquit_ours);
#endif
	}

#ifdef F_GETFL
      tflags_inferior = fcntl (0, F_GETFL, 0);

      /* Is there a reason this is being done twice?  It happens both
         places we use F_SETFL, so I'm inclined to think perhaps there
         is some reason, however perverse.  Perhaps not though...  */
      result = fcntl (0, F_SETFL, tflags_ours);
      result = fcntl (0, F_SETFL, tflags_ours);
#endif

      result = result;		/* lint */
    }
}