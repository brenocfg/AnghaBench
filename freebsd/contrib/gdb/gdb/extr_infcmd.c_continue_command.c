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
typedef  int /*<<< orphan*/  bpstat ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_NO_INFERIOR ; 
 int /*<<< orphan*/  TARGET_SIGNAL_DEFAULT ; 
 int /*<<< orphan*/  async_disable_stdin () ; 
 int bpstat_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_proceed_status () ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ event_loop_p ; 
 scalar_t__ parse_and_eval_long (char*) ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 
 int /*<<< orphan*/  proceed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ignore_count (int,scalar_t__,int) ; 
 int /*<<< orphan*/  stop_bpstat ; 
 int strip_bg_char (char**) ; 
 scalar_t__ target_can_async_p () ; 

void
continue_command (char *proc_count_exp, int from_tty)
{
  int async_exec = 0;
  ERROR_NO_INFERIOR;

  /* Find out whether we must run in the background. */
  if (proc_count_exp != NULL)
    async_exec = strip_bg_char (&proc_count_exp);

  /* If we must run in the background, but the target can't do it,
     error out. */
  if (event_loop_p && async_exec && !target_can_async_p ())
    error ("Asynchronous execution not supported on this target.");

  /* If we are not asked to run in the bg, then prepare to run in the
     foreground, synchronously. */
  if (event_loop_p && !async_exec && target_can_async_p ())
    {
      /* Simulate synchronous execution */
      async_disable_stdin ();
    }

  /* If have argument (besides '&'), set proceed count of breakpoint
     we stopped at.  */
  if (proc_count_exp != NULL)
    {
      bpstat bs = stop_bpstat;
      int num = bpstat_num (&bs);
      if (num == 0 && from_tty)
	{
	  printf_filtered
	    ("Not stopped at any breakpoint; argument ignored.\n");
	}
      while (num != 0)
	{
	  set_ignore_count (num,
			    parse_and_eval_long (proc_count_exp) - 1,
			    from_tty);
	  /* set_ignore_count prints a message ending with a period.
	     So print two spaces before "Continuing.".  */
	  if (from_tty)
	    printf_filtered ("  ");
	  num = bpstat_num (&bs);
	}
    }

  if (from_tty)
    printf_filtered ("Continuing.\n");

  clear_proceed_status ();

  proceed ((CORE_ADDR) -1, TARGET_SIGNAL_DEFAULT, 0);
}