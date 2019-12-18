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
struct cleanup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_UNUSED ; 
 scalar_t__ MON_IDT ; 
 scalar_t__ MON_LSI ; 
 scalar_t__ clear_breakpoint (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mips_desc ; 
 int /*<<< orphan*/  mips_enter_debug () ; 
 int /*<<< orphan*/  mips_error (char*) ; 
 scalar_t__ mips_expect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_initialize_cleanups ; 
 int mips_initializing ; 
 int /*<<< orphan*/  mips_make_srec (char*,char,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mips_monitor ; 
 int /*<<< orphan*/  mips_monitor_prompt ; 
 int /*<<< orphan*/  mips_receive_wait ; 
 int /*<<< orphan*/  mips_request (char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mips_send_command (char*,int) ; 
 scalar_t__ mips_wait_flag ; 
 int monitor_supports_breakpoints ; 
 int /*<<< orphan*/  serial_flush_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_flush_output (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_readchar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_send_break (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_write (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static void
mips_initialize (void)
{
  int err;
  struct cleanup *old_cleanups = make_cleanup (mips_initialize_cleanups, NULL);
  int j;

  /* What is this code doing here?  I don't see any way it can happen, and
     it might mean mips_initializing didn't get cleared properly.
     So I'll make it a warning.  */

  if (mips_initializing)
    {
      warning ("internal error: mips_initialize called twice");
      return;
    }

  mips_wait_flag = 0;
  mips_initializing = 1;

  /* At this point, the packit protocol isn't responding.  We'll try getting
     into the monitor, and restarting the protocol.  */

  /* Force the system into the monitor.  After this we *should* be at
     the mips_monitor_prompt.  */
  if (mips_monitor != MON_IDT)
    j = 0;			/* start by checking if we are already at the prompt */
  else
    j = 1;			/* start by sending a break */
  for (; j <= 4; j++)
    {
      switch (j)
	{
	case 0:		/* First, try sending a CR */
	  serial_flush_input (mips_desc);
	  serial_write (mips_desc, "\r", 1);
	  break;
	case 1:		/* First, try sending a break */
	  serial_send_break (mips_desc);
	  break;
	case 2:		/* Then, try a ^C */
	  serial_write (mips_desc, "\003", 1);
	  break;
	case 3:		/* Then, try escaping from download */
	  {
	    if (mips_monitor != MON_IDT)
	      {
		char tbuff[7];

		/* We shouldn't need to send multiple termination
		   sequences, since the target performs line (or
		   block) reads, and then processes those
		   packets. In-case we were downloading a large packet
		   we flush the output buffer before inserting a
		   termination sequence. */
		serial_flush_output (mips_desc);
		sprintf (tbuff, "\r/E/E\r");
		serial_write (mips_desc, tbuff, 6);
	      }
	    else
	      {
		char srec[10];
		int i;

		/* We are possibly in binary download mode, having
		   aborted in the middle of an S-record.  ^C won't
		   work because of binary mode.  The only reliable way
		   out is to send enough termination packets (8 bytes)
		   to fill up and then overflow the largest size
		   S-record (255 bytes in this case).  This amounts to
		   256/8 + 1 packets.
		 */

		mips_make_srec (srec, '7', 0, NULL, 0);

		for (i = 1; i <= 33; i++)
		  {
		    serial_write (mips_desc, srec, 8);

		    if (serial_readchar (mips_desc, 0) >= 0)
		      break;	/* Break immediatly if we get something from
				   the board. */
		  }
	      }
	  }
	  break;
	case 4:
	  mips_error ("Failed to initialize.");
	}

      if (mips_expect (mips_monitor_prompt))
	break;
    }

  if (mips_monitor != MON_IDT)
    {
      /* Sometimes PMON ignores the first few characters in the first
         command sent after a load.  Sending a blank command gets
         around that.  */
      mips_send_command ("\r", -1);

      /* Ensure the correct target state: */
      if (mips_monitor != MON_LSI)
	mips_send_command ("set regsize 64\r", -1);
      mips_send_command ("set hostport tty0\r", -1);
      mips_send_command ("set brkcmd \"\"\r", -1);
      /* Delete all the current breakpoints: */
      mips_send_command ("db *\r", -1);
      /* NOTE: PMON does not have breakpoint support through the
         "debug" mode, only at the monitor command-line. */
    }

  mips_enter_debug ();

  /* Clear all breakpoints: */
  if ((mips_monitor == MON_IDT
       && clear_breakpoint (-1, 0, BREAK_UNUSED) == 0)
      || mips_monitor == MON_LSI)
    monitor_supports_breakpoints = 1;
  else
    monitor_supports_breakpoints = 0;

  do_cleanups (old_cleanups);

  /* If this doesn't call error, we have connected; we don't care if
     the request itself succeeds or fails.  */

  mips_request ('r', 0, 0, &err, mips_receive_wait, NULL);
}