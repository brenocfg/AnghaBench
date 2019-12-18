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
 int current_function_uses_only_leaf_regs ; 
 scalar_t__ leaf_function_p () ; 
 scalar_t__ only_leaf_regs_used () ; 
 scalar_t__ optimize ; 

__attribute__((used)) static unsigned int
rest_of_handle_check_leaf_regs (void)
{
#ifdef LEAF_REGISTERS
  current_function_uses_only_leaf_regs
    = optimize > 0 && only_leaf_regs_used () && leaf_function_p ();
#endif
  return 0;
}