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
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_NO_INFERIOR ; 
 int TARGET_SIGNAL_0 ; 
 int TARGET_SIGNAL_UNKNOWN ; 
 int /*<<< orphan*/  clear_proceed_status () ; 
 int /*<<< orphan*/  dont_repeat () ; 
 int /*<<< orphan*/  error_no_arg (char*) ; 
 int parse_and_eval_long (char*) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  proceed (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_pc ; 
 int target_signal_from_command (int) ; 
 int target_signal_from_name (char*) ; 
 int /*<<< orphan*/  target_signal_to_name (int) ; 

__attribute__((used)) static void
signal_command (char *signum_exp, int from_tty)
{
  enum target_signal oursig;

  dont_repeat ();		/* Too dangerous.  */
  ERROR_NO_INFERIOR;

  if (!signum_exp)
    error_no_arg ("signal number");

  /* It would be even slicker to make signal names be valid expressions,
     (the type could be "enum $signal" or some such), then the user could
     assign them to convenience variables.  */
  oursig = target_signal_from_name (signum_exp);

  if (oursig == TARGET_SIGNAL_UNKNOWN)
    {
      /* No, try numeric.  */
      int num = parse_and_eval_long (signum_exp);

      if (num == 0)
	oursig = TARGET_SIGNAL_0;
      else
	oursig = target_signal_from_command (num);
    }

  if (from_tty)
    {
      if (oursig == TARGET_SIGNAL_0)
	printf_filtered ("Continuing with no signal.\n");
      else
	printf_filtered ("Continuing with signal %s.\n",
			 target_signal_to_name (oursig));
    }

  clear_proceed_status ();
  /* "signal 0" should not get stuck if we are stopped at a breakpoint.
     FIXME: Neither should "signal foo" but when I tried passing
     (CORE_ADDR)-1 unconditionally I got a testsuite failure which I haven't
     tried to track down yet.  */
  proceed (oursig == TARGET_SIGNAL_0 ? (CORE_ADDR) -1 : stop_pc, oursig, 0);
}