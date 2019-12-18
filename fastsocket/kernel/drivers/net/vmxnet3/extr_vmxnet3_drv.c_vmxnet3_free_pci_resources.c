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
struct vmxnet3_adapter {int /*<<< orphan*/  pdev; int /*<<< orphan*/  hw_addr1; int /*<<< orphan*/  hw_addr0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_selected_regions (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vmxnet3_free_pci_resources(struct vmxnet3_adapter *adapter)
{
	BUG_ON(!adapter->pdev);

	iounmap(adapter->hw_addr0);
	iounmap(adapter->hw_addr1);
	pci_release_selected_regions(adapter->pdev, (1 << 2) - 1);
	pci_disable_device(adapter->pdev);
}