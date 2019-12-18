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
struct pch_gbe_adapter {TYPE_1__* pdev; scalar_t__ have_msi; struct net_device* netdev; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void pch_gbe_free_irq(struct pch_gbe_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;

	free_irq(adapter->pdev->irq, netdev);
	if (adapter->have_msi) {
		pci_disable_msi(adapter->pdev);
		pr_debug("call pci_disable_msi\n");
	}
}