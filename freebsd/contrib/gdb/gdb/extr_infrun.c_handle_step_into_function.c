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
struct symtab_and_line {scalar_t__ line; } ;
struct execution_control_state {scalar_t__ stop_func_start; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  END_STEPPING_RANGE ; 
 scalar_t__ IGNORE_HELPER_CALL (int /*<<< orphan*/ ) ; 
 scalar_t__ SKIP_TRAMPOLINE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ STEP_OVER_ALL ; 
 scalar_t__ STEP_OVER_NONE ; 
 scalar_t__ STEP_OVER_UNDEBUGGABLE ; 
 struct symtab_and_line find_pc_line (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_id_build (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ frame_id_inner (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ in_prologue (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  keep_going (struct execution_control_state*) ; 
 int /*<<< orphan*/  null_frame_id ; 
 scalar_t__ pc_in_sigtramp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prev_pc ; 
 int /*<<< orphan*/  print_stop_reason (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_sp () ; 
 scalar_t__ skip_language_trampoline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  step_frame_id ; 
 int /*<<< orphan*/  step_into_function (struct execution_control_state*) ; 
 scalar_t__ step_over_calls ; 
 int /*<<< orphan*/  step_over_function (struct execution_control_state*) ; 
 int step_range_end ; 
 scalar_t__ step_stop_if_no_debug ; 
 int /*<<< orphan*/  stop_pc ; 
 int stop_step ; 
 int /*<<< orphan*/  stop_stepping (struct execution_control_state*) ; 

__attribute__((used)) static void
handle_step_into_function (struct execution_control_state *ecs)
{
  CORE_ADDR real_stop_pc;

  if ((step_over_calls == STEP_OVER_NONE)
      || ((step_range_end == 1)
          && in_prologue (prev_pc, ecs->stop_func_start)))
    {
      /* I presume that step_over_calls is only 0 when we're
         supposed to be stepping at the assembly language level
         ("stepi").  Just stop.  */
      /* Also, maybe we just did a "nexti" inside a prolog,
         so we thought it was a subroutine call but it was not.
         Stop as well.  FENN */
      stop_step = 1;
      print_stop_reason (END_STEPPING_RANGE, 0);
      stop_stepping (ecs);
      return;
    }

  if (step_over_calls == STEP_OVER_ALL || IGNORE_HELPER_CALL (stop_pc))
    {
      /* We're doing a "next".  */

      if (pc_in_sigtramp (stop_pc)
          && frame_id_inner (step_frame_id,
                             frame_id_build (read_sp (), 0)))
        /* We stepped out of a signal handler, and into its
           calling trampoline.  This is misdetected as a
           subroutine call, but stepping over the signal
           trampoline isn't such a bad idea.  In order to do that,
           we have to ignore the value in step_frame_id, since
           that doesn't represent the frame that'll reach when we
           return from the signal trampoline.  Otherwise we'll
           probably continue to the end of the program.  */
        step_frame_id = null_frame_id;

      step_over_function (ecs);
      keep_going (ecs);
      return;
    }

  /* If we are in a function call trampoline (a stub between
     the calling routine and the real function), locate the real
     function.  That's what tells us (a) whether we want to step
     into it at all, and (b) what prologue we want to run to
     the end of, if we do step into it.  */
  real_stop_pc = skip_language_trampoline (stop_pc);
  if (real_stop_pc == 0)
    real_stop_pc = SKIP_TRAMPOLINE_CODE (stop_pc);
  if (real_stop_pc != 0)
    ecs->stop_func_start = real_stop_pc;

  /* If we have line number information for the function we
     are thinking of stepping into, step into it.

     If there are several symtabs at that PC (e.g. with include
     files), just want to know whether *any* of them have line
     numbers.  find_pc_line handles this.  */
  {
    struct symtab_and_line tmp_sal;

    tmp_sal = find_pc_line (ecs->stop_func_start, 0);
    if (tmp_sal.line != 0)
      {
        step_into_function (ecs);
        return;
      }
  }

  /* If we have no line number and the step-stop-if-no-debug
     is set, we stop the step so that the user has a chance to
     switch in assembly mode.  */
  if (step_over_calls == STEP_OVER_UNDEBUGGABLE && step_stop_if_no_debug)
    {
      stop_step = 1;
      print_stop_reason (END_STEPPING_RANGE, 0);
      stop_stepping (ecs);
      return;
    }

  step_over_function (ecs);
  keep_going (ecs);
  return;
}