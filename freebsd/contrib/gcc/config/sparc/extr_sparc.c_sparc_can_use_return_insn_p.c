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
 scalar_t__ actual_fsize ; 
 int /*<<< orphan*/  sparc_leaf_function_p ; 
 scalar_t__ sparc_prologue_data_valid_p ; 

bool
sparc_can_use_return_insn_p (void)
{
  return sparc_prologue_data_valid_p
	 && (actual_fsize == 0 || !sparc_leaf_function_p);
}