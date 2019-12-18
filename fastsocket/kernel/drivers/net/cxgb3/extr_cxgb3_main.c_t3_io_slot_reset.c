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
struct pci_dev {int dummy; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 struct adapter* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  t3_reenable_adapter (struct adapter*) ; 

__attribute__((used)) static pci_ers_result_t t3_io_slot_reset(struct pci_dev *pdev)
{
	struct adapter *adapter = pci_get_drvdata(pdev);

	if (!t3_reenable_adapter(adapter))
		return PCI_ERS_RESULT_RECOVERED;

	return PCI_ERS_RESULT_DISCONNECT;
}