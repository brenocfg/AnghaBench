#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_vlan_anti_spoofing ) (struct ixgbe_hw*,int,int) ;} ;
struct TYPE_7__ {TYPE_2__ ops; } ;
struct ixgbe_hw {TYPE_3__ mac; } ;
struct ixgbe_adapter {int num_vfs; TYPE_4__* vfinfo; TYPE_1__* pdev; int /*<<< orphan*/  state; scalar_t__ antispoofing_enabled; struct ixgbe_hw hw; } ;
struct TYPE_8__ {int pf_vlan; int pf_qos; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __IXGBE_DOWN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ixgbe_clear_vmvir (struct ixgbe_adapter*,int) ; 
 int ixgbe_set_vf_vlan (struct ixgbe_adapter*,int,int,int) ; 
 int /*<<< orphan*/  ixgbe_set_vmolr (struct ixgbe_hw*,int,int) ; 
 int /*<<< orphan*/  ixgbe_set_vmvir (struct ixgbe_adapter*,int,int,int) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ixgbe_ndo_set_vf_vlan(struct net_device *netdev, int vf, u16 vlan, u8 qos)
{
	int err = 0;
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	struct ixgbe_hw *hw = &adapter->hw;

	if ((vf >= adapter->num_vfs) || (vlan > 4095) || (qos > 7))
		return -EINVAL;
	if (vlan || qos) {
		if (adapter->vfinfo[vf].pf_vlan)
			err = ixgbe_set_vf_vlan(adapter, false,
						adapter->vfinfo[vf].pf_vlan,
						vf);
		if (err)
			goto out;
		err = ixgbe_set_vf_vlan(adapter, true, vlan, vf);
		if (err)
			goto out;
		ixgbe_set_vmvir(adapter, vlan, qos, vf);
		ixgbe_set_vmolr(hw, vf, false);
		if (adapter->antispoofing_enabled)
			hw->mac.ops.set_vlan_anti_spoofing(hw, true, vf);
		adapter->vfinfo[vf].pf_vlan = vlan;
		adapter->vfinfo[vf].pf_qos = qos;
		dev_info(&adapter->pdev->dev,
			 "Setting VLAN %d, QOS 0x%x on VF %d\n", vlan, qos, vf);
		if (test_bit(__IXGBE_DOWN, &adapter->state)) {
			dev_warn(&adapter->pdev->dev,
				 "The VF VLAN has been set,"
				 " but the PF device is not up.\n");
			dev_warn(&adapter->pdev->dev,
				 "Bring the PF device up before"
				 " attempting to use the VF device.\n");
		}
	} else {
		err = ixgbe_set_vf_vlan(adapter, false,
					adapter->vfinfo[vf].pf_vlan, vf);
		ixgbe_clear_vmvir(adapter, vf);
		ixgbe_set_vmolr(hw, vf, true);
		hw->mac.ops.set_vlan_anti_spoofing(hw, false, vf);
		adapter->vfinfo[vf].pf_vlan = 0;
		adapter->vfinfo[vf].pf_qos = 0;
       }
out:
       return err;
}