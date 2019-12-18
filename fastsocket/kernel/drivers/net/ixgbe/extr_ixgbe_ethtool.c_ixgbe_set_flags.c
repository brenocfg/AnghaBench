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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int type; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct ixgbe_adapter {int flags2; scalar_t__ rx_itr_setting; int flags; TYPE_2__ hw; } ;

/* Variables and functions */
 int ETH_FLAG_LRO ; 
 int ETH_FLAG_NTUPLE ; 
 int IXGBE_FLAG2_RSC_CAPABLE ; 
 int IXGBE_FLAG2_RSC_ENABLED ; 
 int IXGBE_FLAG_DCB_ENABLED ; 
 int IXGBE_FLAG_FDIR_HASH_CAPABLE ; 
 int IXGBE_FLAG_FDIR_PERFECT_CAPABLE ; 
 int IXGBE_FLAG_SRIOV_ENABLED ; 
 scalar_t__ IXGBE_MAX_RSC_INT_RATE ; 
 int /*<<< orphan*/  e_info (int /*<<< orphan*/ ,char*) ; 
 int ethtool_op_set_flags (struct net_device*,int) ; 
 int /*<<< orphan*/  ixgbe_adapter_fdir_capable (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_do_reset (struct net_device*) ; 
#define  ixgbe_mac_82599EB 129 
#define  ixgbe_mac_X540 128 
 int /*<<< orphan*/  ixgbe_set_rsc (struct ixgbe_adapter*) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  probe ; 

__attribute__((used)) static int ixgbe_set_flags(struct net_device *netdev, u32 data)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	bool need_reset = false;
	int rc;

	rc = ethtool_op_set_flags(netdev, data);
	if (rc)
		return rc;

	/* if state changes we need to update adapter->flags and reset */
	if ((adapter->flags2 & IXGBE_FLAG2_RSC_CAPABLE) &&
	    (!!(data & ETH_FLAG_LRO) !=
	     !!(adapter->flags2 & IXGBE_FLAG2_RSC_ENABLED))) {
		if ((data & ETH_FLAG_LRO) &&
		    (!adapter->rx_itr_setting ||
		     (adapter->rx_itr_setting > IXGBE_MAX_RSC_INT_RATE))) {
			e_info(probe, "rx-usecs set too low, "
				      "not enabling RSC.\n");
		} else {
			adapter->flags2 ^= IXGBE_FLAG2_RSC_ENABLED;
			switch (adapter->hw.mac.type) {
			case ixgbe_mac_X540:
				ixgbe_set_rsc(adapter);
				break;
			case ixgbe_mac_82599EB:
				need_reset = true;
				break;
			default:
				break;
			}
		}
	}

	/*
	 * Check if Flow Director n-tuple support was enabled or disabled.  If
	 * the state changed, we need to reset.
	 */
	if (!ixgbe_adapter_fdir_capable(adapter))
		goto skip_fdir;

	if (!(adapter->flags & IXGBE_FLAG_FDIR_PERFECT_CAPABLE)) {
		/* turn off ATR, enable perfect filters and reset */
		if (data & ETH_FLAG_NTUPLE) {
			adapter->flags &= ~IXGBE_FLAG_FDIR_HASH_CAPABLE;
			adapter->flags |= IXGBE_FLAG_FDIR_PERFECT_CAPABLE;
			need_reset = true;
		}
	} else if (!(data & ETH_FLAG_NTUPLE)) {
		/* turn off Flow Director, set ATR and reset */
		adapter->flags &= ~IXGBE_FLAG_FDIR_PERFECT_CAPABLE;
		if (!(adapter->flags & IXGBE_FLAG_SRIOV_ENABLED) &&
		    !(adapter->flags & IXGBE_FLAG_DCB_ENABLED))
			adapter->flags |= IXGBE_FLAG_FDIR_HASH_CAPABLE;
		need_reset = true;
	}

skip_fdir:
	if (need_reset)
		ixgbe_do_reset(netdev);
	return 0;

}