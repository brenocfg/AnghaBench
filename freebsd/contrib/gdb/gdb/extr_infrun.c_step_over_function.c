#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct symtab_and_line {void* pc; int /*<<< orphan*/  section; } ;
struct execution_control_state {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  frame_id; } ;

/* Variables and functions */
 void* ADDR_BITS_REMOVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEPRECATED_SAVED_PC_AFTER_CALL (int /*<<< orphan*/ ) ; 
 scalar_t__ DEPRECATED_SAVED_PC_AFTER_CALL_P () ; 
 int /*<<< orphan*/  IN_SOLIB_DYNSYM_RESOLVE_CODE (void*) ; 
 int /*<<< orphan*/  bp_step_resume ; 
 scalar_t__ breakpoints_inserted ; 
 int /*<<< orphan*/  check_for_old_step_resume_breakpoint () ; 
 int /*<<< orphan*/  find_pc_overlay (void*) ; 
 scalar_t__ frame_id_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_pc_unwind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_current_frame () ; 
 int /*<<< orphan*/  get_frame_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_sal (struct symtab_and_line*) ; 
 int /*<<< orphan*/  insert_breakpoints () ; 
 TYPE_1__* set_momentary_breakpoint (struct symtab_and_line,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  step_frame_id ; 
 TYPE_1__* step_resume_breakpoint ; 

__attribute__((used)) static void
step_over_function (struct execution_control_state *ecs)
{
  struct symtab_and_line sr_sal;

  init_sal (&sr_sal);		/* initialize to zeros */

  /* NOTE: cagney/2003-04-06:

     At this point the equality get_frame_pc() == get_frame_func()
     should hold.  This may make it possible for this code to tell the
     frame where it's function is, instead of the reverse.  This would
     avoid the need to search for the frame's function, which can get
     very messy when there is no debug info available (look at the
     heuristic find pc start code found in targets like the MIPS).  */

  /* NOTE: cagney/2003-04-06:

     The intent of DEPRECATED_SAVED_PC_AFTER_CALL was to:

     - provide a very light weight equivalent to frame_unwind_pc()
     (nee FRAME_SAVED_PC) that avoids the prologue analyzer

     - avoid handling the case where the PC hasn't been saved in the
     prologue analyzer

     Unfortunately, not five lines further down, is a call to
     get_frame_id() and that is guarenteed to trigger the prologue
     analyzer.
     
     The `correct fix' is for the prologe analyzer to handle the case
     where the prologue is incomplete (PC in prologue) and,
     consequently, the return pc has not yet been saved.  It should be
     noted that the prologue analyzer needs to handle this case
     anyway: frameless leaf functions that don't save the return PC;
     single stepping through a prologue.

     The d10v handles all this by bailing out of the prologue analsis
     when it reaches the current instruction.  */

  if (DEPRECATED_SAVED_PC_AFTER_CALL_P ())
    sr_sal.pc = ADDR_BITS_REMOVE (DEPRECATED_SAVED_PC_AFTER_CALL (get_current_frame ()));
  else
    sr_sal.pc = ADDR_BITS_REMOVE (frame_pc_unwind (get_current_frame ()));
  sr_sal.section = find_pc_overlay (sr_sal.pc);

  check_for_old_step_resume_breakpoint ();
  step_resume_breakpoint =
    set_momentary_breakpoint (sr_sal, get_frame_id (get_current_frame ()),
			      bp_step_resume);

  if (frame_id_p (step_frame_id)
      && !IN_SOLIB_DYNSYM_RESOLVE_CODE (sr_sal.pc))
    step_resume_breakpoint->frame_id = step_frame_id;

  if (breakpoints_inserted)
    insert_breakpoints ();
}