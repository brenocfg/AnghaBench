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
 int /*<<< orphan*/  branch_target_load_optimize (int) ; 
 int /*<<< orphan*/  cleanup_cfg (int /*<<< orphan*/ ) ; 
 int epilogue_completed ; 
 scalar_t__ flag_branch_target_load_optimize ; 
 int flow2_completed ; 
 int /*<<< orphan*/  get_insns () ; 
 scalar_t__ optimize ; 
 int /*<<< orphan*/  split_all_insns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_prologue_and_epilogue_insns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
rest_of_handle_flow2 (void)
{
  /* If optimizing, then go ahead and split insns now.  */
#ifndef STACK_REGS
  if (optimize > 0)
#endif
    split_all_insns (0);

  if (flag_branch_target_load_optimize)
    branch_target_load_optimize (epilogue_completed);

  if (optimize)
    cleanup_cfg (CLEANUP_EXPENSIVE);

  /* On some machines, the prologue and epilogue code, or parts thereof,
     can be represented as RTL.  Doing so lets us schedule insns between
     it and the rest of the code and also allows delayed branch
     scheduling to operate in the epilogue.  */
  thread_prologue_and_epilogue_insns (get_insns ());
  epilogue_completed = 1;
  flow2_completed = 1;
  return 0;
}