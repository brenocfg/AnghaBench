#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device {int flags; int features; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* update_mc_addr_list ) (struct ixgbe_hw*,struct net_device*) ;} ;
struct TYPE_6__ {scalar_t__ type; TYPE_2__ ops; } ;
struct TYPE_4__ {int user_set_promisc; } ;
struct ixgbe_hw {TYPE_3__ mac; TYPE_1__ addr_ctrl; } ;
struct ixgbe_adapter {int flags; scalar_t__ num_vfs; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  IXGBE_FCTRL ; 
 int IXGBE_FCTRL_BAM ; 
 int IXGBE_FCTRL_DPF ; 
 int IXGBE_FCTRL_MPE ; 
 int IXGBE_FCTRL_PMCF ; 
 int IXGBE_FCTRL_UPE ; 
 int IXGBE_FLAG_SRIOV_ENABLED ; 
 int IXGBE_FLAG_VMDQ_ENABLED ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_VMOLR (int /*<<< orphan*/ ) ; 
 int IXGBE_VMOLR_AUPE ; 
 int IXGBE_VMOLR_BAM ; 
 int IXGBE_VMOLR_MPE ; 
 int IXGBE_VMOLR_ROMPE ; 
 int IXGBE_VMOLR_ROPE ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int NETIF_F_HW_VLAN_RX ; 
 int /*<<< orphan*/  VMDQ_P (int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_mac_82598EB ; 
 int /*<<< orphan*/  ixgbe_restore_vf_multicasts (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_vlan_filter_disable (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_vlan_filter_enable (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_vlan_strip_disable (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_vlan_strip_enable (struct ixgbe_adapter*) ; 
 int ixgbe_write_uc_addr_list (struct net_device*) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,struct net_device*) ; 

void ixgbe_set_rx_mode(struct net_device *netdev)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	struct ixgbe_hw *hw = &adapter->hw;
	u32 fctrl, vmolr = IXGBE_VMOLR_BAM | IXGBE_VMOLR_AUPE;
	int count;

	/* Check for Promiscuous and All Multicast modes */

	fctrl = IXGBE_READ_REG(hw, IXGBE_FCTRL);

	/* set all bits that we expect to always be set */
	fctrl |= IXGBE_FCTRL_BAM;
	fctrl |= IXGBE_FCTRL_DPF; /* discard pause frames when FC enabled */
	fctrl |= IXGBE_FCTRL_PMCF;

	/* clear the bits we are changing the status of */
	fctrl &= ~(IXGBE_FCTRL_UPE | IXGBE_FCTRL_MPE);

	if (netdev->flags & IFF_PROMISC) {
		hw->addr_ctrl.user_set_promisc = true;
		fctrl |= (IXGBE_FCTRL_UPE | IXGBE_FCTRL_MPE);
		vmolr |= (IXGBE_VMOLR_ROPE | IXGBE_VMOLR_MPE);
		/* Only disable hardware filter vlans in promiscuous mode
		 * if SR-IOV and VMDQ are disabled - otherwise ensure
		 * that hardware VLAN filters remain enabled.
		 */
		if (!(adapter->flags & (IXGBE_FLAG_VMDQ_ENABLED |
					IXGBE_FLAG_SRIOV_ENABLED)))
			ixgbe_vlan_filter_disable(adapter);
		else
			ixgbe_vlan_filter_enable(adapter);
	} else {
		if (netdev->flags & IFF_ALLMULTI) {
			fctrl |= IXGBE_FCTRL_MPE;
			vmolr |= IXGBE_VMOLR_MPE;
		}
		ixgbe_vlan_filter_enable(adapter);
		hw->addr_ctrl.user_set_promisc = false;
	}

	/*
	 * Write addresses to available RAR registers, if there is not
	 * sufficient space to store all the addresses then enable
	 * unicast promiscuous mode
	 */
	count = ixgbe_write_uc_addr_list(netdev);
	if (count < 0) {
		fctrl |= IXGBE_FCTRL_UPE;
		vmolr |= IXGBE_VMOLR_ROPE;
	}

	/* Write addresses to the MTA, if the attempt fails
	 * then we should just turn on promiscuous mode so
	 * that we can at least receive multicast traffic
	 */
	hw->mac.ops.update_mc_addr_list(hw, netdev);
	vmolr |= IXGBE_VMOLR_ROMPE;

	if (adapter->num_vfs)
		ixgbe_restore_vf_multicasts(adapter);

	if (hw->mac.type != ixgbe_mac_82598EB) {
		vmolr |= IXGBE_READ_REG(hw, IXGBE_VMOLR(VMDQ_P(0))) &
			 ~(IXGBE_VMOLR_MPE | IXGBE_VMOLR_ROMPE |
			   IXGBE_VMOLR_ROPE);
		IXGBE_WRITE_REG(hw, IXGBE_VMOLR(VMDQ_P(0)), vmolr);
	}

	IXGBE_WRITE_REG(hw, IXGBE_FCTRL, fctrl);

	if (netdev->features & NETIF_F_HW_VLAN_RX)
		ixgbe_vlan_strip_enable(adapter);
	else
		ixgbe_vlan_strip_disable(adapter);
}