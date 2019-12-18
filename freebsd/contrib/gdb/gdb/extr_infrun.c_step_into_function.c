#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct symtab_and_line {scalar_t__ pc; int /*<<< orphan*/  section; } ;
struct symtab {scalar_t__ language; } ;
struct TYPE_2__ {scalar_t__ end; scalar_t__ pc; } ;
struct execution_control_state {scalar_t__ stop_func_start; scalar_t__ stop_func_end; TYPE_1__ sal; } ;

/* Variables and functions */
 int /*<<< orphan*/  END_STEPPING_RANGE ; 
 scalar_t__ SKIP_PROLOGUE (scalar_t__) ; 
 int /*<<< orphan*/  bp_step_resume ; 
 scalar_t__ breakpoints_inserted ; 
 int /*<<< orphan*/  check_for_old_step_resume_breakpoint () ; 
 int /*<<< orphan*/  current_gdbarch ; 
 TYPE_1__ find_pc_line (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_pc_overlay (scalar_t__) ; 
 struct symtab* find_pc_symtab (scalar_t__) ; 
 scalar_t__ gdbarch_adjust_breakpoint_address (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gdbarch_adjust_breakpoint_address_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_sal (struct symtab_and_line*) ; 
 int /*<<< orphan*/  insert_breakpoints () ; 
 int /*<<< orphan*/  keep_going (struct execution_control_state*) ; 
 scalar_t__ language_asm ; 
 int /*<<< orphan*/  null_frame_id ; 
 int /*<<< orphan*/  print_stop_reason (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_momentary_breakpoint (struct symtab_and_line,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  step_range_end ; 
 int /*<<< orphan*/  step_range_start ; 
 int /*<<< orphan*/  step_resume_breakpoint ; 
 scalar_t__ stop_pc ; 
 int stop_step ; 
 int /*<<< orphan*/  stop_stepping (struct execution_control_state*) ; 

__attribute__((used)) static void
step_into_function (struct execution_control_state *ecs)
{
  struct symtab *s;
  struct symtab_and_line sr_sal;

  s = find_pc_symtab (stop_pc);
  if (s && s->language != language_asm)
    ecs->stop_func_start = SKIP_PROLOGUE (ecs->stop_func_start);

  ecs->sal = find_pc_line (ecs->stop_func_start, 0);
  /* Use the step_resume_break to step until the end of the prologue,
     even if that involves jumps (as it seems to on the vax under
     4.2).  */
  /* If the prologue ends in the middle of a source line, continue to
     the end of that source line (if it is still within the function).
     Otherwise, just go to end of prologue.  */
  if (ecs->sal.end
      && ecs->sal.pc != ecs->stop_func_start
      && ecs->sal.end < ecs->stop_func_end)
    ecs->stop_func_start = ecs->sal.end;

  /* Architectures which require breakpoint adjustment might not be able
     to place a breakpoint at the computed address.  If so, the test
     ``ecs->stop_func_start == stop_pc'' will never succeed.  Adjust
     ecs->stop_func_start to an address at which a breakpoint may be
     legitimately placed.
     
     Note:  kevinb/2004-01-19:  On FR-V, if this adjustment is not
     made, GDB will enter an infinite loop when stepping through
     optimized code consisting of VLIW instructions which contain
     subinstructions corresponding to different source lines.  On
     FR-V, it's not permitted to place a breakpoint on any but the
     first subinstruction of a VLIW instruction.  When a breakpoint is
     set, GDB will adjust the breakpoint address to the beginning of
     the VLIW instruction.  Thus, we need to make the corresponding
     adjustment here when computing the stop address.  */
     
  if (gdbarch_adjust_breakpoint_address_p (current_gdbarch))
    {
      ecs->stop_func_start
	= gdbarch_adjust_breakpoint_address (current_gdbarch,
	                                     ecs->stop_func_start);
    }

  if (ecs->stop_func_start == stop_pc)
    {
      /* We are already there: stop now.  */
      stop_step = 1;
      print_stop_reason (END_STEPPING_RANGE, 0);
      stop_stepping (ecs);
      return;
    }
  else
    {
      /* Put the step-breakpoint there and go until there.  */
      init_sal (&sr_sal);	/* initialize to zeroes */
      sr_sal.pc = ecs->stop_func_start;
      sr_sal.section = find_pc_overlay (ecs->stop_func_start);
      /* Do not specify what the fp should be when we stop since on
         some machines the prologue is where the new fp value is
         established.  */
      check_for_old_step_resume_breakpoint ();
      step_resume_breakpoint =
	set_momentary_breakpoint (sr_sal, null_frame_id, bp_step_resume);
      if (breakpoints_inserted)
	insert_breakpoints ();

      /* And make sure stepping stops right away then.  */
      step_range_end = step_range_start;
    }
  keep_going (ecs);
}