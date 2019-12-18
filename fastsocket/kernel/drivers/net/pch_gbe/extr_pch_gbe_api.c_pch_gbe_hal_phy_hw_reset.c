#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pch_gbe_hw {TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset_phy ) (struct pch_gbe_hw*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  stub1 (struct pch_gbe_hw*) ; 

inline void pch_gbe_hal_phy_hw_reset(struct pch_gbe_hw *hw)
{
	if (!hw->func->reset_phy)
		pr_err("ERROR: configuration\n");
	else
		hw->func->reset_phy(hw);
}