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
struct netxen_adapter {int flags; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int NETXEN_NIC_MSIX_ENABLED ; 
 int NETXEN_NIC_MSI_ENABLED ; 
 int /*<<< orphan*/  pci_disable_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_msix (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
netxen_teardown_intr(struct netxen_adapter *adapter)
{
	if (adapter->flags & NETXEN_NIC_MSIX_ENABLED)
		pci_disable_msix(adapter->pdev);
	if (adapter->flags & NETXEN_NIC_MSI_ENABLED)
		pci_disable_msi(adapter->pdev);
}