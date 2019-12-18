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
 int /*<<< orphan*/  TV_JUMP ; 
 int /*<<< orphan*/  cleanup_cfg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cse_condition_code_reg () ; 
 int cse_main (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cse_not_expected ; 
 int /*<<< orphan*/  delete_dead_jumptables () ; 
 int /*<<< orphan*/  delete_trivially_dead_insns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  dump_flags ; 
 int /*<<< orphan*/  dump_flow_info (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  max_reg_num () ; 
 int /*<<< orphan*/  purge_all_dead_edges () ; 
 int /*<<< orphan*/  rebuild_jump_labels (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_scan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
rest_of_handle_cse2 (void)
{
  int tem;

  if (dump_file)
    dump_flow_info (dump_file, dump_flags);

  tem = cse_main (get_insns (), max_reg_num ());

  /* Run a pass to eliminate duplicated assignments to condition code
     registers.  We have to run this after bypass_jumps, because it
     makes it harder for that pass to determine whether a jump can be
     bypassed safely.  */
  cse_condition_code_reg ();

  purge_all_dead_edges ();
  delete_trivially_dead_insns (get_insns (), max_reg_num ());

  if (tem)
    {
      timevar_push (TV_JUMP);
      rebuild_jump_labels (get_insns ());
      delete_dead_jumptables ();
      cleanup_cfg (CLEANUP_EXPENSIVE);
      timevar_pop (TV_JUMP);
    }
  reg_scan (get_insns (), max_reg_num ());
  cse_not_expected = 1;
  return 0;
}