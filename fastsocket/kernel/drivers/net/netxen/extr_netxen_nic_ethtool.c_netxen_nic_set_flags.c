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
typedef  int u32 ;
struct netxen_adapter {int capabilities; int /*<<< orphan*/  rx_csum; } ;
struct net_device {int features; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ETH_FLAG_LRO ; 
 int NETIF_F_LRO ; 
 int NETXEN_NIC_LRO_DISABLED ; 
 int NETXEN_NIC_LRO_ENABLED ; 
 int NX_FW_CAPABILITY_HW_LRO ; 
 int ethtool_op_get_flags (struct net_device*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct netxen_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netxen_config_hw_lro (struct netxen_adapter*,int) ; 
 scalar_t__ netxen_send_lro_cleanup (struct netxen_adapter*) ; 

__attribute__((used)) static int netxen_nic_set_flags(struct net_device *netdev, u32 data)
{
	struct netxen_adapter *adapter = netdev_priv(netdev);
	int hw_lro;

	if ((ethtool_op_get_flags(netdev) & ~ETH_FLAG_LRO) !=
	    (data & ~ETH_FLAG_LRO))
		return -EINVAL;

	if (!(adapter->capabilities & NX_FW_CAPABILITY_HW_LRO))
		return -EINVAL;

	if (!adapter->rx_csum) {
		netdev_info(netdev, "rx csum is off, cannot toggle LRO\n");
		return -EINVAL;
	}

	if (!!(data & ETH_FLAG_LRO) == !!(netdev->features & NETIF_F_LRO))
		return 0;

	if (data & ETH_FLAG_LRO) {
		hw_lro = NETXEN_NIC_LRO_ENABLED;
		netdev->features |= NETIF_F_LRO;
	} else {
		hw_lro = NETXEN_NIC_LRO_DISABLED;
		netdev->features &= ~NETIF_F_LRO;
	}

	if (netxen_config_hw_lro(adapter, hw_lro))
		return -EIO;

	if ((hw_lro == 0) && netxen_send_lro_cleanup(adapter))
		return -EIO;


	return 0;
}