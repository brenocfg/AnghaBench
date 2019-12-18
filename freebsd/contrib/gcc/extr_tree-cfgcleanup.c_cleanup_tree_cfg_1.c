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
 int cleanup_control_flow () ; 
 int cleanup_forwarder_blocks () ; 
 int delete_unreachable_blocks () ; 
 int /*<<< orphan*/  end_recording_case_labels () ; 
 int merge_seq_blocks () ; 
 scalar_t__ optimize ; 
 int /*<<< orphan*/  start_recording_case_labels () ; 

__attribute__((used)) static bool
cleanup_tree_cfg_1 (void)
{
  bool retval;

  retval = cleanup_control_flow ();
  retval |= delete_unreachable_blocks ();

  /* Forwarder blocks can carry line number information which is
     useful when debugging, so we only clean them up when
     optimizing.  */

  if (optimize > 0)
    {
      /* cleanup_forwarder_blocks can redirect edges out of
	 SWITCH_EXPRs, which can get expensive.  So we want to enable
	 recording of edge to CASE_LABEL_EXPR mappings around the call
	 to cleanup_forwarder_blocks.  */
      start_recording_case_labels ();
      retval |= cleanup_forwarder_blocks ();
      end_recording_case_labels ();
    }

  /* Merging the blocks may create new opportunities for folding
     conditional branches (due to the elimination of single-valued PHI
     nodes).  */
  retval |= merge_seq_blocks ();

  return retval;
}