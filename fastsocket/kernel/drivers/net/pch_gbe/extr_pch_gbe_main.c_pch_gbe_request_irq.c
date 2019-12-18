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
struct pch_gbe_adapter {int have_msi; TYPE_1__* pdev; struct net_device* netdev; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int IRQF_SHARED ; 
 int /*<<< orphan*/  pch_gbe_intr ; 
 int pci_enable_msi (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int pch_gbe_request_irq(struct pch_gbe_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	int err;
	int flags;

	flags = IRQF_SHARED;
	adapter->have_msi = false;
	err = pci_enable_msi(adapter->pdev);
	pr_debug("call pci_enable_msi\n");
	if (err) {
		pr_debug("call pci_enable_msi - Error: %d\n", err);
	} else {
		flags = 0;
		adapter->have_msi = true;
	}
	err = request_irq(adapter->pdev->irq, &pch_gbe_intr,
			  flags, netdev->name, netdev);
	if (err)
		pr_err("Unable to allocate interrupt Error: %d\n", err);
	pr_debug("adapter->have_msi : %d  flags : 0x%04x  return : 0x%04x\n",
		 adapter->have_msi, flags, err);
	return err;
}