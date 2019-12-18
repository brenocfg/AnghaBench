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
 int CLEANUP_EXPENSIVE ; 
 int CLEANUP_THREADING ; 
 int /*<<< orphan*/  cleanup_cfg (int) ; 
 int /*<<< orphan*/  delete_trivially_dead_insns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  dump_flags ; 
 int /*<<< orphan*/  dump_flow_info (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expected_value_to_br_prob () ; 
 scalar_t__ flag_guess_branch_prob ; 
 scalar_t__ flag_thread_jumps ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  max_reg_num () ; 
 scalar_t__ optimize ; 
 int /*<<< orphan*/  purge_line_number_notes () ; 
 int /*<<< orphan*/  reg_scan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  renumber_insns () ; 

__attribute__((used)) static unsigned int
rest_of_handle_jump2 (void)
{
  /* Turn NOTE_INSN_EXPECTED_VALUE into REG_BR_PROB.  Do this
     before jump optimization switches branch directions.  */
  if (flag_guess_branch_prob)
    expected_value_to_br_prob ();

  delete_trivially_dead_insns (get_insns (), max_reg_num ());
  reg_scan (get_insns (), max_reg_num ());
  if (dump_file)
    dump_flow_info (dump_file, dump_flags);
  cleanup_cfg ((optimize ? CLEANUP_EXPENSIVE : 0)
	       | (flag_thread_jumps ? CLEANUP_THREADING : 0));

  purge_line_number_notes ();

  if (optimize)
    cleanup_cfg (CLEANUP_EXPENSIVE);

  /* Jump optimization, and the removal of NULL pointer checks, may
     have reduced the number of instructions substantially.  CSE, and
     future passes, allocate arrays whose dimensions involve the
     maximum instruction UID, so if we can reduce the maximum UID
     we'll save big on memory.  */
  renumber_insns ();
  return 0;
}