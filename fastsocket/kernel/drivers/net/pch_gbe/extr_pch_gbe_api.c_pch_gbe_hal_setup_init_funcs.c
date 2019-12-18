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
struct pch_gbe_hw {int /*<<< orphan*/  reg; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  pch_gbe_plat_init_function_pointers (struct pch_gbe_hw*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

inline s32 pch_gbe_hal_setup_init_funcs(struct pch_gbe_hw *hw)
{
	if (!hw->reg) {
		pr_err("ERROR: Registers not mapped\n");
		return -ENOSYS;
	}
	pch_gbe_plat_init_function_pointers(hw);
	return 0;
}