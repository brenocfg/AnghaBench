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
struct execution_control_state {scalar_t__ another_trap; scalar_t__ remove_breakpoints_on_following_step; scalar_t__ update_step_sp; } ;

/* Variables and functions */
 size_t TARGET_SIGNAL_0 ; 
 size_t TARGET_SIGNAL_TRAP ; 
 scalar_t__ breakpoints_failed ; 
 int breakpoints_inserted ; 
 int /*<<< orphan*/  currently_stepping (struct execution_control_state*) ; 
 scalar_t__ insert_breakpoints () ; 
 int /*<<< orphan*/  prepare_to_wait (struct execution_control_state*) ; 
 int /*<<< orphan*/  prev_pc ; 
 int /*<<< orphan*/  read_pc () ; 
 int /*<<< orphan*/  read_sp () ; 
 int /*<<< orphan*/  remove_breakpoints () ; 
 int /*<<< orphan*/  resume (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * signal_program ; 
 int /*<<< orphan*/ * step_resume_breakpoint ; 
 int /*<<< orphan*/  step_sp ; 
 size_t stop_signal ; 
 int /*<<< orphan*/  stop_stepping (struct execution_control_state*) ; 
 int /*<<< orphan*/ * through_sigtramp_breakpoint ; 
 scalar_t__ trap_expected ; 

__attribute__((used)) static void
keep_going (struct execution_control_state *ecs)
{
  /* Save the pc before execution, to compare with pc after stop.  */
  prev_pc = read_pc ();		/* Might have been DECR_AFTER_BREAK */

  if (ecs->update_step_sp)
    step_sp = read_sp ();
  ecs->update_step_sp = 0;

  /* If we did not do break;, it means we should keep running the
     inferior and not return to debugger.  */

  if (trap_expected && stop_signal != TARGET_SIGNAL_TRAP)
    {
      /* We took a signal (which we are supposed to pass through to
         the inferior, else we'd have done a break above) and we
         haven't yet gotten our trap.  Simply continue.  */
      resume (currently_stepping (ecs), stop_signal);
    }
  else
    {
      /* Either the trap was not expected, but we are continuing
         anyway (the user asked that this signal be passed to the
         child)
         -- or --
         The signal was SIGTRAP, e.g. it was our signal, but we
         decided we should resume from it.

         We're going to run this baby now!

         Insert breakpoints now, unless we are trying to one-proceed
         past a breakpoint.  */
      /* If we've just finished a special step resume and we don't
         want to hit a breakpoint, pull em out.  */
      if (step_resume_breakpoint == NULL
	  && through_sigtramp_breakpoint == NULL
	  && ecs->remove_breakpoints_on_following_step)
	{
	  ecs->remove_breakpoints_on_following_step = 0;
	  remove_breakpoints ();
	  breakpoints_inserted = 0;
	}
      else if (!breakpoints_inserted &&
	       (through_sigtramp_breakpoint != NULL || !ecs->another_trap))
	{
	  breakpoints_failed = insert_breakpoints ();
	  if (breakpoints_failed)
	    {
	      stop_stepping (ecs);
	      return;
	    }
	  breakpoints_inserted = 1;
	}

      trap_expected = ecs->another_trap;

      /* Do not deliver SIGNAL_TRAP (except when the user explicitly
         specifies that such a signal should be delivered to the
         target program).

         Typically, this would occure when a user is debugging a
         target monitor on a simulator: the target monitor sets a
         breakpoint; the simulator encounters this break-point and
         halts the simulation handing control to GDB; GDB, noteing
         that the break-point isn't valid, returns control back to the
         simulator; the simulator then delivers the hardware
         equivalent of a SIGNAL_TRAP to the program being debugged. */

      if (stop_signal == TARGET_SIGNAL_TRAP && !signal_program[stop_signal])
	stop_signal = TARGET_SIGNAL_0;


      resume (currently_stepping (ecs), stop_signal);
    }

  prepare_to_wait (ecs);
}