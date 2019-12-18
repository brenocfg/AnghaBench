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
 int /*<<< orphan*/  cleanup_cfg (int /*<<< orphan*/ ) ; 
 int cse_main (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cse_not_expected ; 
 int /*<<< orphan*/  delete_dead_jumptables () ; 
 int /*<<< orphan*/  delete_trivially_dead_insns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_unreachable_blocks () ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  dump_flags ; 
 int /*<<< orphan*/  dump_flow_info (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_gcse ; 
 int /*<<< orphan*/  flag_rerun_cse_after_loop ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  max_reg_num () ; 
 int optimize ; 
 scalar_t__ purge_all_dead_edges () ; 
 int /*<<< orphan*/  rebuild_jump_labels (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_scan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
rest_of_handle_cse (void)
{
  int tem;

  if (dump_file)
    dump_flow_info (dump_file, dump_flags);

  reg_scan (get_insns (), max_reg_num ());

  tem = cse_main (get_insns (), max_reg_num ());
  if (tem)
    rebuild_jump_labels (get_insns ());
  if (purge_all_dead_edges ())
    delete_unreachable_blocks ();

  delete_trivially_dead_insns (get_insns (), max_reg_num ());

  /* If we are not running more CSE passes, then we are no longer
     expecting CSE to be run.  But always rerun it in a cheap mode.  */
  cse_not_expected = !flag_rerun_cse_after_loop && !flag_gcse;

  if (tem)
    delete_dead_jumptables ();

  if (tem || optimize > 1)
    cleanup_cfg (CLEANUP_EXPENSIVE);
  return 0;
}