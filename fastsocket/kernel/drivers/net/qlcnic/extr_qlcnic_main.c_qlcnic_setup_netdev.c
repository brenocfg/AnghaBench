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
struct qlcnic_adapter {int rx_csum; TYPE_2__* msix_entries; TYPE_1__* ahw; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int watchdog_timeo; int features; int vlan_features; int /*<<< orphan*/  irq; int /*<<< orphan*/  mtu; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  vector; } ;
struct TYPE_3__ {int capabilities; int /*<<< orphan*/  max_mc_count; scalar_t__ mc_enabled; } ;

/* Variables and functions */
 int HZ ; 
 int NETIF_F_GRO ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_HW_VLAN_FILTER ; 
 int NETIF_F_HW_VLAN_RX ; 
 int NETIF_F_HW_VLAN_TX ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_LRO ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int QLCNIC_FW_CAPABILITY_HW_LRO ; 
 scalar_t__ QLCNIC_IS_TSO_CAPABLE (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  QLCNIC_MAX_MC_COUNT ; 
 int QLCNIC_WATCHDOG_TIMEOUTVALUE ; 
 int /*<<< orphan*/  SET_ETHTOOL_OPS (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  qlcnic_change_mtu (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_ethtool_ops ; 
 int /*<<< orphan*/  qlcnic_ethtool_ops_ext ; 
 int /*<<< orphan*/  qlcnic_netdev_ops ; 
 scalar_t__ qlcnic_sriov_vf_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_vf_ethtool_ops ; 
 scalar_t__ qlcnic_vlan_tx_check (struct qlcnic_adapter*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  set_ethtool_ops_ext (struct net_device*,int /*<<< orphan*/ *) ; 

int qlcnic_setup_netdev(struct qlcnic_adapter *adapter,
			struct net_device *netdev, int pci_using_dac)
{
	int err;
	struct pci_dev *pdev = adapter->pdev;

	adapter->rx_csum = 1;
	adapter->ahw->mc_enabled = 0;
	adapter->ahw->max_mc_count = QLCNIC_MAX_MC_COUNT;

	netdev->netdev_ops	   = &qlcnic_netdev_ops;
	netdev->watchdog_timeo     = QLCNIC_WATCHDOG_TIMEOUTVALUE * HZ;

	qlcnic_change_mtu(netdev, netdev->mtu);

	if (qlcnic_sriov_vf_check(adapter))
		SET_ETHTOOL_OPS(netdev, &qlcnic_sriov_vf_ethtool_ops);
	else
		SET_ETHTOOL_OPS(netdev, &qlcnic_ethtool_ops);

	set_ethtool_ops_ext(netdev, &qlcnic_ethtool_ops_ext);

	netdev->features |= (NETIF_F_SG | NETIF_F_IP_CSUM |
			     NETIF_F_IPV6_CSUM | NETIF_F_GRO |
			     NETIF_F_HW_VLAN_RX);
	netdev->vlan_features |= (NETIF_F_SG | NETIF_F_IP_CSUM |
				  NETIF_F_IPV6_CSUM | NETIF_F_GRO);

	if (QLCNIC_IS_TSO_CAPABLE(adapter)) {
		netdev->features |= (NETIF_F_TSO | NETIF_F_TSO6);
		netdev->vlan_features |= (NETIF_F_TSO | NETIF_F_TSO6);
	}

	if (pci_using_dac) {
		netdev->features |= NETIF_F_HIGHDMA;
		netdev->vlan_features |= NETIF_F_HIGHDMA;
	}

	if (qlcnic_vlan_tx_check(adapter))
		netdev->features |= (NETIF_F_HW_VLAN_TX);

	if (qlcnic_sriov_vf_check(adapter))
		netdev->features |= NETIF_F_HW_VLAN_FILTER;

	if (adapter->ahw->capabilities & QLCNIC_FW_CAPABILITY_HW_LRO)
		netdev->features |= NETIF_F_LRO;

	netdev->irq = adapter->msix_entries[0].vector;

	err = register_netdev(netdev);
	if (err) {
		dev_err(&pdev->dev, "failed to register net device\n");
		return err;
	}

	return 0;
}