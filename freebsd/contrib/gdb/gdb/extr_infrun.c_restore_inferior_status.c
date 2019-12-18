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
struct inferior_status {int /*<<< orphan*/  selected_frame_id; scalar_t__ restore_stack_info; int /*<<< orphan*/  registers; int /*<<< orphan*/  stop_registers; int /*<<< orphan*/  proceed_to_finish; int /*<<< orphan*/  breakpoint_proceeded; int /*<<< orphan*/  stop_bpstat; int /*<<< orphan*/  stop_soon; int /*<<< orphan*/  stop_after_trap; int /*<<< orphan*/  step_over_calls; int /*<<< orphan*/  step_frame_id; int /*<<< orphan*/  step_range_end; int /*<<< orphan*/  step_range_start; int /*<<< orphan*/  trap_expected; int /*<<< orphan*/  stopped_by_random_signal; int /*<<< orphan*/  stop_stack_dummy; int /*<<< orphan*/  stop_step; int /*<<< orphan*/  stop_pc; int /*<<< orphan*/  stop_signal; } ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_MASK_ERROR ; 
 int /*<<< orphan*/  bpstat_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  breakpoint_proceeded ; 
 scalar_t__ catch_errors (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_regcache ; 
 int /*<<< orphan*/  get_current_frame () ; 
 int /*<<< orphan*/  proceed_to_finish ; 
 int /*<<< orphan*/  regcache_cpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_xfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_selected_frame ; 
 int /*<<< orphan*/  select_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  step_frame_id ; 
 int /*<<< orphan*/  step_over_calls ; 
 int /*<<< orphan*/  step_range_end ; 
 int /*<<< orphan*/  step_range_start ; 
 int /*<<< orphan*/  stop_after_trap ; 
 int /*<<< orphan*/  stop_bpstat ; 
 int /*<<< orphan*/  stop_pc ; 
 int /*<<< orphan*/  stop_registers ; 
 int /*<<< orphan*/  stop_signal ; 
 int /*<<< orphan*/  stop_soon ; 
 int /*<<< orphan*/  stop_stack_dummy ; 
 int /*<<< orphan*/  stop_step ; 
 int /*<<< orphan*/  stopped_by_random_signal ; 
 scalar_t__ target_has_execution ; 
 scalar_t__ target_has_stack ; 
 int /*<<< orphan*/  trap_expected ; 
 int /*<<< orphan*/  xfree (struct inferior_status*) ; 

void
restore_inferior_status (struct inferior_status *inf_status)
{
  stop_signal = inf_status->stop_signal;
  stop_pc = inf_status->stop_pc;
  stop_step = inf_status->stop_step;
  stop_stack_dummy = inf_status->stop_stack_dummy;
  stopped_by_random_signal = inf_status->stopped_by_random_signal;
  trap_expected = inf_status->trap_expected;
  step_range_start = inf_status->step_range_start;
  step_range_end = inf_status->step_range_end;
  step_frame_id = inf_status->step_frame_id;
  step_over_calls = inf_status->step_over_calls;
  stop_after_trap = inf_status->stop_after_trap;
  stop_soon = inf_status->stop_soon;
  bpstat_clear (&stop_bpstat);
  stop_bpstat = inf_status->stop_bpstat;
  breakpoint_proceeded = inf_status->breakpoint_proceeded;
  proceed_to_finish = inf_status->proceed_to_finish;

  /* FIXME: Is the restore of stop_registers always needed. */
  regcache_xfree (stop_registers);
  stop_registers = inf_status->stop_registers;

  /* The inferior can be gone if the user types "print exit(0)"
     (and perhaps other times).  */
  if (target_has_execution)
    /* NB: The register write goes through to the target.  */
    regcache_cpy (current_regcache, inf_status->registers);
  regcache_xfree (inf_status->registers);

  /* FIXME: If we are being called after stopping in a function which
     is called from gdb, we should not be trying to restore the
     selected frame; it just prints a spurious error message (The
     message is useful, however, in detecting bugs in gdb (like if gdb
     clobbers the stack)).  In fact, should we be restoring the
     inferior status at all in that case?  .  */

  if (target_has_stack && inf_status->restore_stack_info)
    {
      /* The point of catch_errors is that if the stack is clobbered,
         walking the stack might encounter a garbage pointer and
         error() trying to dereference it.  */
      if (catch_errors
	  (restore_selected_frame, &inf_status->selected_frame_id,
	   "Unable to restore previously selected frame:\n",
	   RETURN_MASK_ERROR) == 0)
	/* Error in restoring the selected frame.  Select the innermost
	   frame.  */
	select_frame (get_current_frame ());

    }

  xfree (inf_status);
}