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
struct pch_gbe_adapter {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCH_GBE_MAR_ENTRIES ; 
 scalar_t__ pch_gbe_hal_init_hw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pch_gbe_mac_init_rx_addrs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_gbe_mac_reset_hw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

void pch_gbe_reset(struct pch_gbe_adapter *adapter)
{
	pch_gbe_mac_reset_hw(&adapter->hw);
	/* Setup the receive address. */
	pch_gbe_mac_init_rx_addrs(&adapter->hw, PCH_GBE_MAR_ENTRIES);
	if (pch_gbe_hal_init_hw(&adapter->hw))
		pr_err("Hardware Error\n");
}