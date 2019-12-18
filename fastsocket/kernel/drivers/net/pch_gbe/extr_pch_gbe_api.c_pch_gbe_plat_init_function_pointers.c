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
struct TYPE_2__ {int /*<<< orphan*/  reset_delay_us; } ;
struct pch_gbe_hw {int /*<<< orphan*/ * func; TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCH_GBE_PHY_RESET_DELAY_US ; 
 int /*<<< orphan*/  pch_gbe_ops ; 

__attribute__((used)) static void pch_gbe_plat_init_function_pointers(struct pch_gbe_hw *hw)
{
	/* Set PHY parameter */
	hw->phy.reset_delay_us     = PCH_GBE_PHY_RESET_DELAY_US;
	/* Set function pointers */
	hw->func = &pch_gbe_ops;
}