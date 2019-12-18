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
struct execution_control_state {int /*<<< orphan*/  ptid; int /*<<< orphan*/  current_symtab; int /*<<< orphan*/  current_line; int /*<<< orphan*/  stepping_through_sigtramp; int /*<<< orphan*/  stepping_through_solib_catchpoints; int /*<<< orphan*/  stepping_through_solib_after_catch; int /*<<< orphan*/  another_trap; int /*<<< orphan*/  handling_longjmp; } ;

/* Variables and functions */
 scalar_t__ in_thread_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  load_infrun_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prev_pc ; 
 int /*<<< orphan*/  save_infrun_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  step_frame_id ; 
 int /*<<< orphan*/  step_range_end ; 
 int /*<<< orphan*/  step_range_start ; 
 int /*<<< orphan*/  step_resume_breakpoint ; 
 int /*<<< orphan*/  step_sp ; 
 int /*<<< orphan*/  through_sigtramp_breakpoint ; 
 int /*<<< orphan*/  trap_expected ; 

__attribute__((used)) static void
context_switch (struct execution_control_state *ecs)
{
  /* Caution: it may happen that the new thread (or the old one!)
     is not in the thread list.  In this case we must not attempt
     to "switch context", or we run the risk that our context may
     be lost.  This may happen as a result of the target module
     mishandling thread creation.  */

  if (in_thread_list (inferior_ptid) && in_thread_list (ecs->ptid))
    {				/* Perform infrun state context switch: */
      /* Save infrun state for the old thread.  */
      save_infrun_state (inferior_ptid, prev_pc,
			 trap_expected, step_resume_breakpoint,
			 through_sigtramp_breakpoint, step_range_start,
			 step_range_end, &step_frame_id,
			 ecs->handling_longjmp, ecs->another_trap,
			 ecs->stepping_through_solib_after_catch,
			 ecs->stepping_through_solib_catchpoints,
			 ecs->stepping_through_sigtramp,
			 ecs->current_line, ecs->current_symtab, step_sp);

      /* Load infrun state for the new thread.  */
      load_infrun_state (ecs->ptid, &prev_pc,
			 &trap_expected, &step_resume_breakpoint,
			 &through_sigtramp_breakpoint, &step_range_start,
			 &step_range_end, &step_frame_id,
			 &ecs->handling_longjmp, &ecs->another_trap,
			 &ecs->stepping_through_solib_after_catch,
			 &ecs->stepping_through_solib_catchpoints,
			 &ecs->stepping_through_sigtramp,
			 &ecs->current_line, &ecs->current_symtab, &step_sp);
    }
  inferior_ptid = ecs->ptid;
}