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

/* Variables and functions */
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 int /*<<< orphan*/  VEC_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calculate_dominance_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_tree_cfg () ; 
 int /*<<< orphan*/  free_dominance_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap ; 
 int /*<<< orphan*/  stack ; 
 int thread_through_all_blocks () ; 
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static void
finalize_jump_threads (void)
{
  bool cfg_altered = false;
  cfg_altered = thread_through_all_blocks ();

  /* If we threaded jumps, then we need to recompute the dominance
     information, to safely do that we must clean up the CFG first.  */
  if (cfg_altered)
    {
      free_dominance_info (CDI_DOMINATORS);
      cleanup_tree_cfg ();
      calculate_dominance_info (CDI_DOMINATORS);
    }
  VEC_free (tree, heap, stack);
}