#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct adapter {TYPE_1__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ pci_enable_device (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_restore_state (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_save_state (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_set_master (TYPE_1__*) ; 
 int /*<<< orphan*/  t3_free_sge_resources (struct adapter*) ; 
 scalar_t__ t3_replay_prep_adapter (struct adapter*) ; 

__attribute__((used)) static int t3_reenable_adapter(struct adapter *adapter)
{
	if (pci_enable_device(adapter->pdev)) {
		dev_err(&adapter->pdev->dev,
			"Cannot re-enable PCI device after reset.\n");
		goto err;
	}
	pci_set_master(adapter->pdev);
	pci_restore_state(adapter->pdev);
	pci_save_state(adapter->pdev);

	/* Free sge resources */
	t3_free_sge_resources(adapter);

	if (t3_replay_prep_adapter(adapter))
		goto err;

	return 0;
err:
	return -1;
}