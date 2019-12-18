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
struct frame_info {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_NO_INFERIOR ; 
 int /*<<< orphan*/  STEP_OVER_ALL ; 
 int /*<<< orphan*/  STEP_OVER_NONE ; 
 int /*<<< orphan*/  TARGET_SIGNAL_DEFAULT ; 
 int /*<<< orphan*/  async_disable_stdin () ; 
 int /*<<< orphan*/  clear_proceed_status () ; 
 int /*<<< orphan*/  disable_longjmp_breakpoint_cleanup ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  enable_longjmp_breakpoint () ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ event_loop_p ; 
 int /*<<< orphan*/  find_pc_line_pc_range (int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ find_pc_partial_function (int /*<<< orphan*/ ,char**,int*,int*) ; 
 struct frame_info* get_current_frame () ; 
 int /*<<< orphan*/  get_frame_id (struct frame_info*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_exec_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int parse_and_eval_long (char*) ; 
 int /*<<< orphan*/  printf_filtered (char*,char*) ; 
 int /*<<< orphan*/  proceed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_sp () ; 
 int /*<<< orphan*/  step_frame_id ; 
 int step_multi ; 
 int /*<<< orphan*/  step_once (int,int,int) ; 
 int /*<<< orphan*/  step_over_calls ; 
 int step_range_end ; 
 int step_range_start ; 
 int /*<<< orphan*/  step_sp ; 
 int /*<<< orphan*/  stop_pc ; 
 int /*<<< orphan*/  stop_step ; 
 int strip_bg_char (char**) ; 
 scalar_t__ target_can_async_p () ; 
 int /*<<< orphan*/  target_terminal_ours () ; 

__attribute__((used)) static void
step_1 (int skip_subroutines, int single_inst, char *count_string)
{
  int count = 1;
  struct frame_info *frame;
  struct cleanup *cleanups = 0;
  int async_exec = 0;

  ERROR_NO_INFERIOR;

  if (count_string)
    async_exec = strip_bg_char (&count_string);

  /* If we get a request for running in the bg but the target
     doesn't support it, error out. */
  if (event_loop_p && async_exec && !target_can_async_p ())
    error ("Asynchronous execution not supported on this target.");

  /* If we don't get a request of running in the bg, then we need
     to simulate synchronous (fg) execution. */
  if (event_loop_p && !async_exec && target_can_async_p ())
    {
      /* Simulate synchronous execution */
      async_disable_stdin ();
    }

  count = count_string ? parse_and_eval_long (count_string) : 1;

  if (!single_inst || skip_subroutines)		/* leave si command alone */
    {
      enable_longjmp_breakpoint ();
      if (!event_loop_p || !target_can_async_p ())
	cleanups = make_cleanup (disable_longjmp_breakpoint_cleanup, 0 /*ignore*/);
      else
        make_exec_cleanup (disable_longjmp_breakpoint_cleanup, 0 /*ignore*/);
    }

  /* In synchronous case, all is well, just use the regular for loop. */
  if (!event_loop_p || !target_can_async_p ())
    {
      for (; count > 0; count--)
	{
	  clear_proceed_status ();

	  frame = get_current_frame ();
	  if (!frame)		/* Avoid coredump here.  Why tho? */
	    error ("No current frame");
	  step_frame_id = get_frame_id (frame);
	  step_sp = read_sp ();

	  if (!single_inst)
	    {
	      find_pc_line_pc_range (stop_pc, &step_range_start, &step_range_end);
	      if (step_range_end == 0)
		{
		  char *name;
		  if (find_pc_partial_function (stop_pc, &name, &step_range_start,
						&step_range_end) == 0)
		    error ("Cannot find bounds of current function");

		  target_terminal_ours ();
		  printf_filtered ("\
Single stepping until exit from function %s, \n\
which has no line number information.\n", name);
		}
	    }
	  else
	    {
	      /* Say we are stepping, but stop after one insn whatever it does.  */
	      step_range_start = step_range_end = 1;
	      if (!skip_subroutines)
		/* It is stepi.
		   Don't step over function calls, not even to functions lacking
		   line numbers.  */
		step_over_calls = STEP_OVER_NONE;
	    }

	  if (skip_subroutines)
	    step_over_calls = STEP_OVER_ALL;

	  step_multi = (count > 1);
	  proceed ((CORE_ADDR) -1, TARGET_SIGNAL_DEFAULT, 1);

	  if (!stop_step)
	    break;
	}

      if (!single_inst || skip_subroutines)
	do_cleanups (cleanups);
      return;
    }
  /* In case of asynchronous target things get complicated, do only
     one step for now, before returning control to the event loop. Let
     the continuation figure out how many other steps we need to do,
     and handle them one at the time, through step_once(). */
  else
    {
      if (event_loop_p && target_can_async_p ())
	step_once (skip_subroutines, single_inst, count);
    }
}