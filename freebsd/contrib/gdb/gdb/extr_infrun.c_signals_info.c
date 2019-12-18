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

/* Variables and functions */
 int /*<<< orphan*/  QUIT ; 
 int TARGET_SIGNAL_0 ; 
 int TARGET_SIGNAL_DEFAULT ; 
 int TARGET_SIGNAL_FIRST ; 
 scalar_t__ TARGET_SIGNAL_LAST ; 
 int TARGET_SIGNAL_UNKNOWN ; 
 int /*<<< orphan*/  parse_and_eval_long (char*) ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 
 int /*<<< orphan*/  sig_print_header () ; 
 int /*<<< orphan*/  sig_print_info (int) ; 
 int target_signal_from_command (int /*<<< orphan*/ ) ; 
 int target_signal_from_name (char*) ; 

__attribute__((used)) static void
signals_info (char *signum_exp, int from_tty)
{
  enum target_signal oursig;
  sig_print_header ();

  if (signum_exp)
    {
      /* First see if this is a symbol name.  */
      oursig = target_signal_from_name (signum_exp);
      if (oursig == TARGET_SIGNAL_UNKNOWN)
	{
	  /* No, try numeric.  */
	  oursig =
	    target_signal_from_command (parse_and_eval_long (signum_exp));
	}
      sig_print_info (oursig);
      return;
    }

  printf_filtered ("\n");
  /* These ugly casts brought to you by the native VAX compiler.  */
  for (oursig = TARGET_SIGNAL_FIRST;
       (int) oursig < (int) TARGET_SIGNAL_LAST;
       oursig = (enum target_signal) ((int) oursig + 1))
    {
      QUIT;

      if (oursig != TARGET_SIGNAL_UNKNOWN
	  && oursig != TARGET_SIGNAL_DEFAULT && oursig != TARGET_SIGNAL_0)
	sig_print_info (oursig);
    }

  printf_filtered ("\nUse the \"handle\" command to change these tables.\n");
}