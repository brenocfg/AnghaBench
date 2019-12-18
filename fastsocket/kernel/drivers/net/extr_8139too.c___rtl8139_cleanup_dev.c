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
struct rtl8139_private {scalar_t__ mmio_addr; struct pci_dev* pci_dev; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct rtl8139_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __rtl8139_cleanup_dev (struct net_device *dev)
{
	struct rtl8139_private *tp = netdev_priv(dev);
	struct pci_dev *pdev;

	assert (dev != NULL);
	assert (tp->pci_dev != NULL);
	pdev = tp->pci_dev;

	if (tp->mmio_addr)
		pci_iounmap (pdev, tp->mmio_addr);

	/* it's ok to call this even if we have no regions to free */
	pci_release_regions (pdev);

	free_netdev(dev);
	pci_set_drvdata (pdev, NULL);
}