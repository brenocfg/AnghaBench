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
typedef  int /*<<< orphan*/  bitmap ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 int /*<<< orphan*/  TODO_update_ssa ; 
 int /*<<< orphan*/  calculate_dominance_info (int /*<<< orphan*/ ) ; 
 int cleanup_tree_cfg () ; 
 int /*<<< orphan*/  current_loops ; 
 int /*<<< orphan*/  fix_loop_structure (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rewrite_into_loop_closed_ssa (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scev_reset () ; 
 int /*<<< orphan*/  verify_loop_structure (int /*<<< orphan*/ ) ; 

void
cleanup_tree_cfg_loop (void)
{
  bool changed = cleanup_tree_cfg ();

  if (changed)
    {
      bitmap changed_bbs = BITMAP_ALLOC (NULL);
      fix_loop_structure (current_loops, changed_bbs);
      calculate_dominance_info (CDI_DOMINATORS);

      /* This usually does nothing.  But sometimes parts of cfg that originally
	 were inside a loop get out of it due to edge removal (since they
	 become unreachable by back edges from latch).  */
      rewrite_into_loop_closed_ssa (changed_bbs, TODO_update_ssa);

      BITMAP_FREE (changed_bbs);

#ifdef ENABLE_CHECKING
      verify_loop_structure (current_loops);
#endif
      scev_reset ();
    }
}