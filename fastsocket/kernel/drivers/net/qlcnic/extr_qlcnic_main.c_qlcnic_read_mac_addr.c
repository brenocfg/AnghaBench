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
typedef  int /*<<< orphan*/  u8 ;
struct qlcnic_adapter {int /*<<< orphan*/ * mac_addr; struct pci_dev* pdev; struct net_device* netdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int addr_len; int /*<<< orphan*/ * dev_addr; int /*<<< orphan*/ * perm_addr; } ;

/* Variables and functions */
 int EIO ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ qlcnic_get_mac_address (struct qlcnic_adapter*,int /*<<< orphan*/ *) ; 

int qlcnic_read_mac_addr(struct qlcnic_adapter *adapter)
{
	u8 mac_addr[ETH_ALEN];
	struct net_device *netdev = adapter->netdev;
	struct pci_dev *pdev = adapter->pdev;

	if (qlcnic_get_mac_address(adapter, mac_addr) != 0)
		return -EIO;

	memcpy(netdev->dev_addr, mac_addr, ETH_ALEN);
	memcpy(netdev->perm_addr, netdev->dev_addr, netdev->addr_len);
	memcpy(adapter->mac_addr, netdev->dev_addr, netdev->addr_len);

	/* set station address */

	if (!is_valid_ether_addr(netdev->perm_addr))
		dev_warn(&pdev->dev, "Bad MAC address %pM.\n",
					netdev->dev_addr);

	return 0;
}