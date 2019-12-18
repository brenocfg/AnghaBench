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

/* Variables and functions */
 scalar_t__ TARGET_SIGNAL_0 ; 
 int bpstat_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_hex_string (unsigned long) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  stop_bpstat ; 
 scalar_t__ stop_pc ; 
 scalar_t__ stop_signal ; 
 scalar_t__ stop_step ; 
 int /*<<< orphan*/  target_files_info () ; 
 int /*<<< orphan*/  target_has_execution ; 
 int /*<<< orphan*/  target_signal_to_name (scalar_t__) ; 
 int /*<<< orphan*/  target_signal_to_string (scalar_t__) ; 

__attribute__((used)) static void
program_info (char *args, int from_tty)
{
  bpstat bs = stop_bpstat;
  int num = bpstat_num (&bs);

  if (!target_has_execution)
    {
      printf_filtered ("The program being debugged is not being run.\n");
      return;
    }

  target_files_info ();
  printf_filtered ("Program stopped at %s.\n",
		   local_hex_string ((unsigned long) stop_pc));
  if (stop_step)
    printf_filtered ("It stopped after being stepped.\n");
  else if (num != 0)
    {
      /* There may be several breakpoints in the same place, so this
         isn't as strange as it seems.  */
      while (num != 0)
	{
	  if (num < 0)
	    {
	      printf_filtered ("It stopped at a breakpoint that has ");
	      printf_filtered ("since been deleted.\n");
	    }
	  else
	    printf_filtered ("It stopped at breakpoint %d.\n", num);
	  num = bpstat_num (&bs);
	}
    }
  else if (stop_signal != TARGET_SIGNAL_0)
    {
      printf_filtered ("It stopped with signal %s, %s.\n",
		       target_signal_to_name (stop_signal),
		       target_signal_to_string (stop_signal));
    }

  if (!from_tty)
    {
      printf_filtered ("Type \"info stack\" or \"info registers\" ");
      printf_filtered ("for more information.\n");
    }
}