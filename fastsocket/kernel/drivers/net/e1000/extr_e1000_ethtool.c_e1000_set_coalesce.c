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
struct net_device {int dummy; } ;
struct ethtool_coalesce {int rx_coalesce_usecs; } ;
struct e1000_hw {scalar_t__ mac_type; } ;
struct e1000_adapter {int itr; int itr_setting; struct e1000_hw hw; } ;

/* Variables and functions */
 int E1000_MAX_ITR_USECS ; 
 int E1000_MIN_ITR_USECS ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ITR ; 
 scalar_t__ e1000_82545 ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int e1000_set_coalesce(struct net_device *netdev,
			      struct ethtool_coalesce *ec)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;

	if (hw->mac_type < e1000_82545)
		return -EOPNOTSUPP;

	if ((ec->rx_coalesce_usecs > E1000_MAX_ITR_USECS) ||
	    ((ec->rx_coalesce_usecs > 4) &&
	     (ec->rx_coalesce_usecs < E1000_MIN_ITR_USECS)) ||
	    (ec->rx_coalesce_usecs == 2))
		return -EINVAL;

	if (ec->rx_coalesce_usecs == 4) {
		adapter->itr = adapter->itr_setting = 4;
	} else if (ec->rx_coalesce_usecs <= 3) {
		adapter->itr = 20000;
		adapter->itr_setting = ec->rx_coalesce_usecs;
	} else {
		adapter->itr = (1000000 / ec->rx_coalesce_usecs);
		adapter->itr_setting = adapter->itr & ~3;
	}

	if (adapter->itr_setting != 0)
		ew32(ITR, 1000000000 / (adapter->itr * 256));
	else
		ew32(ITR, 0);

	return 0;
}