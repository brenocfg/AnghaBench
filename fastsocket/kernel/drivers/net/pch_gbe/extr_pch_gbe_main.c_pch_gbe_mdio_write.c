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
struct pch_gbe_hw {int dummy; } ;
struct pch_gbe_adapter {struct pch_gbe_hw hw; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCH_GBE_HAL_MIIM_WRITE ; 
 struct pch_gbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pch_gbe_mac_ctrl_miim (struct pch_gbe_hw*,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void pch_gbe_mdio_write(struct net_device *netdev,
			       int addr, int reg, int data)
{
	struct pch_gbe_adapter *adapter = netdev_priv(netdev);
	struct pch_gbe_hw *hw = &adapter->hw;

	pch_gbe_mac_ctrl_miim(hw, addr, PCH_GBE_HAL_MIIM_WRITE, reg, data);
}