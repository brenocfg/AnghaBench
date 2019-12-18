#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct ixgbe_adapter {int num_vfs; TYPE_2__* pdev; int /*<<< orphan*/  state; TYPE_1__* vfinfo; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int pf_set_mac; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __IXGBE_DOWN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int ixgbe_set_vf_mac (struct ixgbe_adapter*,int,int /*<<< orphan*/ *) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ixgbe_ndo_set_vf_mac(struct net_device *netdev, int vf, u8 *mac)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	if (!is_valid_ether_addr(mac) || (vf >= adapter->num_vfs))
		return -EINVAL;
	adapter->vfinfo[vf].pf_set_mac = true;
	dev_info(&adapter->pdev->dev, "setting MAC %pM on VF %d\n", mac, vf);
	dev_info(&adapter->pdev->dev, "Reload the VF driver to make this"
				      " change effective.");
	if (test_bit(__IXGBE_DOWN, &adapter->state)) {
		dev_warn(&adapter->pdev->dev, "The VF MAC address has been set,"
			 " but the PF device is not up.\n");
		dev_warn(&adapter->pdev->dev, "Bring the PF device up before"
			 " attempting to use the VF device.\n");
	}
	return ixgbe_set_vf_mac(adapter, vf, mac);
}