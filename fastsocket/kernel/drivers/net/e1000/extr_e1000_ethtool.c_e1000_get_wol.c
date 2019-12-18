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
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int supported; int wolopts; } ;
struct e1000_hw {int device_id; } ;
struct e1000_adapter {int wol; TYPE_1__* pdev; struct e1000_hw hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  E1000_DEV_ID_82546GB_QUAD_COPPER_KSP3 128 
 int E1000_WUFC_BC ; 
 int E1000_WUFC_EX ; 
 int E1000_WUFC_MAG ; 
 int E1000_WUFC_MC ; 
 int WAKE_BCAST ; 
 int WAKE_MAGIC ; 
 int WAKE_MCAST ; 
 int WAKE_UCAST ; 
 int /*<<< orphan*/  device_can_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drv ; 
 scalar_t__ e1000_wol_exclusion (struct e1000_adapter*,struct ethtool_wolinfo*) ; 
 int /*<<< orphan*/  e_err (int /*<<< orphan*/ ,char*) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void e1000_get_wol(struct net_device *netdev,
			  struct ethtool_wolinfo *wol)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;

	wol->supported = WAKE_UCAST | WAKE_MCAST |
	                 WAKE_BCAST | WAKE_MAGIC;
	wol->wolopts = 0;

	/* this function will set ->supported = 0 and return 1 if wol is not
	 * supported by this hardware */
	if (e1000_wol_exclusion(adapter, wol) ||
	    !device_can_wakeup(&adapter->pdev->dev))
		return;

	/* apply any specific unsupported masks here */
	switch (hw->device_id) {
	case E1000_DEV_ID_82546GB_QUAD_COPPER_KSP3:
		/* KSP3 does not suppport UCAST wake-ups */
		wol->supported &= ~WAKE_UCAST;

		if (adapter->wol & E1000_WUFC_EX)
			e_err(drv, "Interface does not support directed "
			      "(unicast) frame wake-up packets\n");
		break;
	default:
		break;
	}

	if (adapter->wol & E1000_WUFC_EX)
		wol->wolopts |= WAKE_UCAST;
	if (adapter->wol & E1000_WUFC_MC)
		wol->wolopts |= WAKE_MCAST;
	if (adapter->wol & E1000_WUFC_BC)
		wol->wolopts |= WAKE_BCAST;
	if (adapter->wol & E1000_WUFC_MAG)
		wol->wolopts |= WAKE_MAGIC;
}