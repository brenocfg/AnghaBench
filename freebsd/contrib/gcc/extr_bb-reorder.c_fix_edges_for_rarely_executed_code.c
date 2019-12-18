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
typedef  int /*<<< orphan*/  edge ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_LONG_COND_BRANCH ; 
 int /*<<< orphan*/  HAS_LONG_UNCOND_BRANCH ; 
 int /*<<< orphan*/  add_labels_and_missing_jumps (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  add_reg_crossing_jump_notes () ; 
 int /*<<< orphan*/  fix_crossing_conditional_branches () ; 
 int /*<<< orphan*/  fix_crossing_unconditional_branches () ; 
 int /*<<< orphan*/  fix_up_fall_thru_edges () ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  max_reg_num () ; 
 int /*<<< orphan*/  reg_scan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fix_edges_for_rarely_executed_code (edge *crossing_edges,
				    int n_crossing_edges)
{
  /* Make sure the source of any crossing edge ends in a jump and the
     destination of any crossing edge has a label.  */

  add_labels_and_missing_jumps (crossing_edges, n_crossing_edges);

  /* Convert all crossing fall_thru edges to non-crossing fall
     thrus to unconditional jumps (that jump to the original fall
     thru dest).  */

  fix_up_fall_thru_edges ();

  /* If the architecture does not have conditional branches that can
     span all of memory, convert crossing conditional branches into
     crossing unconditional branches.  */

  if (!HAS_LONG_COND_BRANCH)
    fix_crossing_conditional_branches ();

  /* If the architecture does not have unconditional branches that
     can span all of memory, convert crossing unconditional branches
     into indirect jumps.  Since adding an indirect jump also adds
     a new register usage, update the register usage information as
     well.  */

  if (!HAS_LONG_UNCOND_BRANCH)
    {
      fix_crossing_unconditional_branches ();
      reg_scan (get_insns(), max_reg_num ());
    }

  add_reg_crossing_jump_notes ();
}