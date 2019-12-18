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
struct pci_dev {scalar_t__ msi_enabled; scalar_t__ msix_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msix (struct pci_dev*) ; 

__attribute__((used)) static void cleanup_service_irqs(struct pci_dev *dev)
{
	if (dev->msix_enabled)
		pci_disable_msix(dev);
	else if (dev->msi_enabled)
		pci_disable_msi(dev);
}