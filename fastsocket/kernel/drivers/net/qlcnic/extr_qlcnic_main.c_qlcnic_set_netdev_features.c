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
struct qlcnic_esw_func_cfg {int offload_flags; } ;
struct qlcnic_adapter {int rx_csum; int flags; TYPE_1__* pdev; struct net_device* netdev; } ;
struct net_device {int features; unsigned long vlan_features; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT_0 ; 
 int BIT_1 ; 
 int BIT_2 ; 
 unsigned long NETIF_F_GRO ; 
 unsigned long NETIF_F_IPV6_CSUM ; 
 unsigned long NETIF_F_IP_CSUM ; 
 int NETIF_F_LRO ; 
 unsigned long NETIF_F_SG ; 
 unsigned long NETIF_F_TSO ; 
 unsigned long NETIF_F_TSO6 ; 
 scalar_t__ QLCNIC_IS_TSO_CAPABLE (struct qlcnic_adapter*) ; 
 int QLCNIC_LRO_DISABLED ; 
 int QLCNIC_LRO_ENABLED ; 
 int QLCNIC_LRO_WAS_ENABLED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_config_hw_lro (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  qlcnic_send_lro_cleanup (struct qlcnic_adapter*) ; 

__attribute__((used)) static void qlcnic_set_netdev_features(struct qlcnic_adapter *adapter,
				       struct qlcnic_esw_func_cfg *esw_cfg)
{
	struct net_device *netdev = adapter->netdev;
	unsigned long features, vlan_features;
	int hw_lro;

	if (qlcnic_83xx_check(adapter))
		return;

	features = (NETIF_F_SG | NETIF_F_IP_CSUM |
			NETIF_F_IPV6_CSUM | NETIF_F_GRO);
	vlan_features = (NETIF_F_SG | NETIF_F_IP_CSUM |
			NETIF_F_IPV6_CSUM | NETIF_F_GRO);

	if (QLCNIC_IS_TSO_CAPABLE(adapter)) {
		features |= (NETIF_F_TSO | NETIF_F_TSO6);
		vlan_features |= (NETIF_F_TSO | NETIF_F_TSO6);
	}

	if (netdev->features & NETIF_F_LRO)
		features |= NETIF_F_LRO;

	if (esw_cfg->offload_flags & BIT_0) {
		adapter->rx_csum = 1;
		if (adapter->flags & QLCNIC_LRO_WAS_ENABLED) {
			hw_lro = QLCNIC_LRO_ENABLED;
			if (qlcnic_config_hw_lro(adapter, hw_lro))
				return;
			dev_info(&adapter->pdev->dev,
				 "Enabling LRO as Rx checksum is on\n");
			netdev->features |= NETIF_F_LRO;
		}
		netdev->features |= features;
		if (!(esw_cfg->offload_flags & BIT_1)) {
			netdev->features &= ~NETIF_F_TSO;
			features &= ~NETIF_F_TSO;
		}
		if (!(esw_cfg->offload_flags & BIT_2)) {
			netdev->features &= ~NETIF_F_TSO6;
			features &= ~NETIF_F_TSO6;
		}
	} else {
		if (netdev->features & NETIF_F_LRO) {
			hw_lro = QLCNIC_LRO_DISABLED;
			if (qlcnic_config_hw_lro(adapter, hw_lro))
				return;

			if (qlcnic_82xx_check(adapter))
				qlcnic_send_lro_cleanup(adapter);
			dev_info(&adapter->pdev->dev,
				 "Disabling LRO as rx_csum is off\n");
			adapter->flags |= QLCNIC_LRO_WAS_ENABLED;
		}
		netdev->features &= ~features;
		features &= ~features;
		adapter->rx_csum = 0;
	}

	netdev->vlan_features = (features & vlan_features);
}