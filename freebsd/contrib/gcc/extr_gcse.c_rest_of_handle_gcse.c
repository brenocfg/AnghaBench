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
 int /*<<< orphan*/  TV_CSE ; 
 int /*<<< orphan*/  TV_JUMP ; 
 int /*<<< orphan*/  cleanup_cfg (int /*<<< orphan*/ ) ; 
 int cse_main (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cse_not_expected ; 
 int /*<<< orphan*/  delete_dead_jumptables () ; 
 int /*<<< orphan*/  delete_trivially_dead_insns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int flag_cse_follow_jumps ; 
 int flag_cse_skip_blocks ; 
 scalar_t__ flag_expensive_optimizations ; 
 int /*<<< orphan*/  flag_rerun_cse_after_loop ; 
 int gcse_main (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  max_reg_num () ; 
 int /*<<< orphan*/  purge_all_dead_edges () ; 
 int /*<<< orphan*/  rebuild_jump_labels (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_scan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
rest_of_handle_gcse (void)
{
  int save_csb, save_cfj;
  int tem2 = 0, tem;

  tem = gcse_main (get_insns ());
  rebuild_jump_labels (get_insns ());
  delete_trivially_dead_insns (get_insns (), max_reg_num ());

  save_csb = flag_cse_skip_blocks;
  save_cfj = flag_cse_follow_jumps;
  flag_cse_skip_blocks = flag_cse_follow_jumps = 0;

  /* If -fexpensive-optimizations, re-run CSE to clean up things done
     by gcse.  */
  if (flag_expensive_optimizations)
    {
      timevar_push (TV_CSE);
      reg_scan (get_insns (), max_reg_num ());
      tem2 = cse_main (get_insns (), max_reg_num ());
      purge_all_dead_edges ();
      delete_trivially_dead_insns (get_insns (), max_reg_num ());
      timevar_pop (TV_CSE);
      cse_not_expected = !flag_rerun_cse_after_loop;
    }

  /* If gcse or cse altered any jumps, rerun jump optimizations to clean
     things up.  */
  if (tem || tem2)
    {
      timevar_push (TV_JUMP);
      rebuild_jump_labels (get_insns ());
      delete_dead_jumptables ();
      cleanup_cfg (CLEANUP_EXPENSIVE);
      timevar_pop (TV_JUMP);
    }

  flag_cse_skip_blocks = save_csb;
  flag_cse_follow_jumps = save_cfj;
  return 0;
}