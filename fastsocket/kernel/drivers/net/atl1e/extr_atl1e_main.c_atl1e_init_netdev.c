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
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct net_device {int features; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_TX_WATCHDOG ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_HW_VLAN_RX ; 
 int NETIF_F_HW_VLAN_TX ; 
 int NETIF_F_LLTX ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atl1e_netdev_ops ; 
 int /*<<< orphan*/  atl1e_set_ethtool_ops (struct net_device*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct net_device*) ; 

__attribute__((used)) static int atl1e_init_netdev(struct net_device *netdev, struct pci_dev *pdev)
{
	SET_NETDEV_DEV(netdev, &pdev->dev);
	pci_set_drvdata(pdev, netdev);

	netdev->irq  = pdev->irq;
	netdev->netdev_ops = &atl1e_netdev_ops;

	netdev->watchdog_timeo = AT_TX_WATCHDOG;
	atl1e_set_ethtool_ops(netdev);

	netdev->features = NETIF_F_SG | NETIF_F_HW_CSUM |
		NETIF_F_HW_VLAN_TX | NETIF_F_HW_VLAN_RX;
	netdev->features |= NETIF_F_LLTX;
	netdev->features |= NETIF_F_TSO;

	return 0;
}