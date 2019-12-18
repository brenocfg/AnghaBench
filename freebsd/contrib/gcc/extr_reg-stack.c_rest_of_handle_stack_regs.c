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
 int CLEANUP_CROSSJUMP ; 
 int CLEANUP_EXPENSIVE ; 
 int CLEANUP_POST_REGSTACK ; 
 scalar_t__ cleanup_cfg (int) ; 
 scalar_t__ flag_crossjumping ; 
 scalar_t__ flag_reorder_blocks ; 
 scalar_t__ flag_reorder_blocks_and_partition ; 
 scalar_t__ optimize ; 
 scalar_t__ reg_to_stack () ; 
 int regstack_completed ; 
 int /*<<< orphan*/  reorder_basic_blocks (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
rest_of_handle_stack_regs (void)
{
#ifdef STACK_REGS
  if (reg_to_stack () && optimize)
    {
      regstack_completed = 1;
      if (cleanup_cfg (CLEANUP_EXPENSIVE | CLEANUP_POST_REGSTACK
                       | (flag_crossjumping ? CLEANUP_CROSSJUMP : 0))
          && (flag_reorder_blocks || flag_reorder_blocks_and_partition))
        {
          reorder_basic_blocks (0);
          cleanup_cfg (CLEANUP_EXPENSIVE | CLEANUP_POST_REGSTACK);
        }
    }
  else 
    regstack_completed = 1;
#endif
  return 0;
}