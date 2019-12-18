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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ STEP_SKIPS_DELAY (scalar_t__) ; 
 scalar_t__ STEP_SKIPS_DELAY_P ; 
 size_t TARGET_SIGNAL_0 ; 
 int TARGET_SIGNAL_DEFAULT ; 
 int /*<<< orphan*/  annotate_starting () ; 
 scalar_t__ bpstat_should_step () ; 
 scalar_t__ breakpoint_here_p (scalar_t__) ; 
 int breakpoints_inserted ; 
 int /*<<< orphan*/  event_loop_p ; 
 int /*<<< orphan*/  find_pc_function (scalar_t__) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  insert_breakpoints () ; 
 int /*<<< orphan*/  normal_stop () ; 
 scalar_t__ prepare_to_proceed () ; 
 scalar_t__ prev_pc ; 
 scalar_t__ read_pc () ; 
 int /*<<< orphan*/  resume (int,size_t) ; 
 int /*<<< orphan*/ * signal_program ; 
 int /*<<< orphan*/  step_start_function ; 
 int stop_after_trap ; 
 scalar_t__ stop_pc ; 
 size_t stop_signal ; 
 int /*<<< orphan*/  target_can_async_p () ; 
 int trap_expected ; 
 scalar_t__ trap_expected_after_continue ; 
 int /*<<< orphan*/  wait_for_inferior () ; 
 int /*<<< orphan*/  write_pc (scalar_t__) ; 

void
proceed (CORE_ADDR addr, enum target_signal siggnal, int step)
{
  int oneproc = 0;

  if (step > 0)
    step_start_function = find_pc_function (read_pc ());
  if (step < 0)
    stop_after_trap = 1;

  if (addr == (CORE_ADDR) -1)
    {
      /* If there is a breakpoint at the address we will resume at,
         step one instruction before inserting breakpoints
         so that we do not stop right away (and report a second
         hit at this breakpoint).  */

      if (read_pc () == stop_pc && breakpoint_here_p (read_pc ()))
	oneproc = 1;

#ifndef STEP_SKIPS_DELAY
#define STEP_SKIPS_DELAY(pc) (0)
#define STEP_SKIPS_DELAY_P (0)
#endif
      /* Check breakpoint_here_p first, because breakpoint_here_p is fast
         (it just checks internal GDB data structures) and STEP_SKIPS_DELAY
         is slow (it needs to read memory from the target).  */
      if (STEP_SKIPS_DELAY_P
	  && breakpoint_here_p (read_pc () + 4)
	  && STEP_SKIPS_DELAY (read_pc ()))
	oneproc = 1;
    }
  else
    {
      write_pc (addr);
    }

  /* In a multi-threaded task we may select another thread
     and then continue or step.

     But if the old thread was stopped at a breakpoint, it
     will immediately cause another breakpoint stop without
     any execution (i.e. it will report a breakpoint hit
     incorrectly).  So we must step over it first.

     prepare_to_proceed checks the current thread against the thread
     that reported the most recent event.  If a step-over is required
     it returns TRUE and sets the current thread to the old thread. */
  if (prepare_to_proceed () && breakpoint_here_p (read_pc ()))
    oneproc = 1;

#ifdef HP_OS_BUG
  if (trap_expected_after_continue)
    {
      /* If (step == 0), a trap will be automatically generated after
         the first instruction is executed.  Force step one
         instruction to clear this condition.  This should not occur
         if step is nonzero, but it is harmless in that case.  */
      oneproc = 1;
      trap_expected_after_continue = 0;
    }
#endif /* HP_OS_BUG */

  if (oneproc)
    /* We will get a trace trap after one instruction.
       Continue it automatically and insert breakpoints then.  */
    trap_expected = 1;
  else
    {
      insert_breakpoints ();
      /* If we get here there was no call to error() in 
	 insert breakpoints -- so they were inserted.  */
      breakpoints_inserted = 1;
    }

  if (siggnal != TARGET_SIGNAL_DEFAULT)
    stop_signal = siggnal;
  /* If this signal should not be seen by program,
     give it zero.  Used for debugging signals.  */
  else if (!signal_program[stop_signal])
    stop_signal = TARGET_SIGNAL_0;

  annotate_starting ();

  /* Make sure that output from GDB appears before output from the
     inferior.  */
  gdb_flush (gdb_stdout);

  /* Refresh prev_pc value just prior to resuming.  This used to be
     done in stop_stepping, however, setting prev_pc there did not handle
     scenarios such as inferior function calls or returning from
     a function via the return command.  In those cases, the prev_pc
     value was not set properly for subsequent commands.  The prev_pc value 
     is used to initialize the starting line number in the ecs.  With an 
     invalid value, the gdb next command ends up stopping at the position
     represented by the next line table entry past our start position.
     On platforms that generate one line table entry per line, this
     is not a problem.  However, on the ia64, the compiler generates
     extraneous line table entries that do not increase the line number.
     When we issue the gdb next command on the ia64 after an inferior call
     or a return command, we often end up a few instructions forward, still 
     within the original line we started.

     An attempt was made to have init_execution_control_state () refresh
     the prev_pc value before calculating the line number.  This approach
     did not work because on platforms that use ptrace, the pc register
     cannot be read unless the inferior is stopped.  At that point, we
     are not guaranteed the inferior is stopped and so the read_pc ()
     call can fail.  Setting the prev_pc value here ensures the value is 
     updated correctly when the inferior is stopped.  */  
  prev_pc = read_pc ();

  /* Resume inferior.  */
  resume (oneproc || step || bpstat_should_step (), stop_signal);

  /* Wait for it to stop (if not standalone)
     and in any case decode why it stopped, and act accordingly.  */
  /* Do this only if we are not using the event loop, or if the target
     does not support asynchronous execution. */
  if (!event_loop_p || !target_can_async_p ())
    {
      wait_for_inferior ();
      normal_stop ();
    }
}