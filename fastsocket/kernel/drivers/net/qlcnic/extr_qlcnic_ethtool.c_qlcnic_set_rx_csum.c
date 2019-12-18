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
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_adapter {int flags; int rx_csum; TYPE_1__* pdev; } ;
struct net_device {int features; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int EOPNOTSUPP ; 
 int NETIF_F_LRO ; 
 int QLCNIC_ESWITCH_ENABLED ; 
 int /*<<< orphan*/  QLCNIC_LRO_DISABLED ; 
 int /*<<< orphan*/  QLCNIC_LRO_ENABLED ; 
 int QLCNIC_LRO_WAS_ENABLED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_config_hw_lro (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_send_lro_cleanup (struct qlcnic_adapter*) ; 

__attribute__((used)) static int qlcnic_set_rx_csum(struct net_device *dev, u32 data)
{
	struct qlcnic_adapter *adapter = netdev_priv(dev);

	if ((adapter->flags & QLCNIC_ESWITCH_ENABLED &&
	    qlcnic_82xx_check(adapter)))
		return -EOPNOTSUPP;
	if (!!data) {
		adapter->rx_csum = !!data;
		if (adapter->flags & QLCNIC_LRO_WAS_ENABLED) {
			if (qlcnic_config_hw_lro(adapter, QLCNIC_LRO_ENABLED))
				return -EIO;
			dev->features |= NETIF_F_LRO;
			dev_info(&adapter->pdev->dev,
				 "Enabling LRO as Rx checksum is on\n");
		}
		return 0;
	}

	if (dev->features & NETIF_F_LRO) {
		if (qlcnic_config_hw_lro(adapter, QLCNIC_LRO_DISABLED))
			return -EIO;

		dev->features &= ~NETIF_F_LRO;
		qlcnic_send_lro_cleanup(adapter);
		dev_info(&adapter->pdev->dev,
			 "Disabling LRO as rx_csum is off\n");
		adapter->flags |= QLCNIC_LRO_WAS_ENABLED;
	}
	adapter->rx_csum = !!data;
	return 0;
}