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
 int /*<<< orphan*/  CLEANUP_EXPENSIVE ; 
 scalar_t__ NUM_FIXED_BLOCKS ; 
 int /*<<< orphan*/  cfg_layout_finalize () ; 
 int /*<<< orphan*/  cfg_layout_initialize (unsigned int) ; 
 int /*<<< orphan*/  cleanup_cfg (int /*<<< orphan*/ ) ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  dump_flags ; 
 int /*<<< orphan*/  dump_flow_info (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layout_superblocks () ; 
 int /*<<< orphan*/  mark_dfs_back_edges () ; 
 scalar_t__ n_basic_blocks ; 
 int /*<<< orphan*/  tail_duplicate () ; 

void
tracer (unsigned int flags)
{
  if (n_basic_blocks <= NUM_FIXED_BLOCKS + 1)
    return;

  cfg_layout_initialize (flags);
  mark_dfs_back_edges ();
  if (dump_file)
    dump_flow_info (dump_file, dump_flags);
  tail_duplicate ();
  layout_superblocks ();
  if (dump_file)
    dump_flow_info (dump_file, dump_flags);
  cfg_layout_finalize ();

  /* Merge basic blocks in duplicated traces.  */
  cleanup_cfg (CLEANUP_EXPENSIVE);
}