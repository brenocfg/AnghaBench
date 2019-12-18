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
typedef  scalar_t__ u32 ;
struct net_device {int /*<<< orphan*/  features; } ;
struct TYPE_4__ {int type; } ;
struct TYPE_3__ {TYPE_2__ mac; } ;
struct ixgbe_adapter {int flags2; TYPE_1__ hw; } ;

/* Variables and functions */
 int IXGBE_FLAG2_RSC_CAPABLE ; 
 int IXGBE_FLAG2_RSC_ENABLED ; 
 int /*<<< orphan*/  NETIF_F_LRO ; 
 int /*<<< orphan*/  NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  ixgbe_do_reset (struct net_device*) ; 
#define  ixgbe_mac_82599EB 129 
#define  ixgbe_mac_X540 128 
 int /*<<< orphan*/  ixgbe_set_rsc (struct ixgbe_adapter*) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ixgbe_set_rx_csum(struct net_device *netdev, u32 data)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	bool need_reset = false;

	if (data) {
		netdev->features |= NETIF_F_RXCSUM;
	} else {
		netdev->features &= ~NETIF_F_RXCSUM;

		if (adapter->flags2 & IXGBE_FLAG2_RSC_CAPABLE) {
			adapter->flags2 &= ~IXGBE_FLAG2_RSC_ENABLED;
			netdev->features &= ~NETIF_F_LRO;
		}

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

	if (need_reset)
		ixgbe_do_reset(netdev);

	return 0;
}