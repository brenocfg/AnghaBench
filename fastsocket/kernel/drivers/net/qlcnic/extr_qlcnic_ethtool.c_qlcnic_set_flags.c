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
struct qlcnic_adapter {TYPE_1__* pdev; int /*<<< orphan*/  rx_csum; TYPE_2__* ahw; } ;
struct net_device {int features; } ;
struct TYPE_4__ {int capabilities; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ETH_FLAG_LRO ; 
 int NETIF_F_LRO ; 
 int QLCNIC_FW_CAPABILITY_HW_LRO ; 
 int QLCNIC_LRO_ENABLED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_config_hw_lro (struct qlcnic_adapter*,int) ; 
 scalar_t__ qlcnic_send_lro_cleanup (struct qlcnic_adapter*) ; 

__attribute__((used)) static int qlcnic_set_flags(struct net_device *netdev, u32 data)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	int hw_lro;

	if (data & ETH_FLAG_LRO) {
		if (netdev->features & NETIF_F_LRO)
			return 0;

		if (!(adapter->ahw->capabilities & QLCNIC_FW_CAPABILITY_HW_LRO))
			return -EINVAL;

		if (!adapter->rx_csum) {
			dev_info(&adapter->pdev->dev, "rx csum is off, "
				"cannot toggle lro\n");
			return -EINVAL;
		}

		hw_lro = QLCNIC_LRO_ENABLED;
		netdev->features |= NETIF_F_LRO;
	} else {

		if (!(netdev->features & NETIF_F_LRO))
			return 0;

		hw_lro = 0;
		netdev->features &= ~NETIF_F_LRO;
	}

	if (qlcnic_config_hw_lro(adapter, hw_lro))
		return -EIO;

	if (!hw_lro && qlcnic_82xx_check(adapter)) {
		if (qlcnic_send_lro_cleanup(adapter))
			return -EIO;
	}

	return 0;
}