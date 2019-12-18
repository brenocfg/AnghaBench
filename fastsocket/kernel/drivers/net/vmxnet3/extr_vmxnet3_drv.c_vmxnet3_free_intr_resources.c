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
struct TYPE_2__ {scalar_t__ type; } ;
struct vmxnet3_adapter {TYPE_1__ intr; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ VMXNET3_IT_INTX ; 
 scalar_t__ VMXNET3_IT_MSI ; 
 scalar_t__ VMXNET3_IT_MSIX ; 
 int /*<<< orphan*/  pci_disable_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_msix (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vmxnet3_free_intr_resources(struct vmxnet3_adapter *adapter)
{
	if (adapter->intr.type == VMXNET3_IT_MSIX)
		pci_disable_msix(adapter->pdev);
	else if (adapter->intr.type == VMXNET3_IT_MSI)
		pci_disable_msi(adapter->pdev);
	else
		BUG_ON(adapter->intr.type != VMXNET3_IT_INTX);
}