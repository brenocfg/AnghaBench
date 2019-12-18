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
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  int pci_channel_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  ipr_pci_frozen (struct pci_dev*) ; 
 int /*<<< orphan*/  ipr_pci_perm_failure (struct pci_dev*) ; 
#define  pci_channel_io_frozen 129 
#define  pci_channel_io_perm_failure 128 

__attribute__((used)) static pci_ers_result_t ipr_pci_error_detected(struct pci_dev *pdev,
					       pci_channel_state_t state)
{
	switch (state) {
	case pci_channel_io_frozen:
		ipr_pci_frozen(pdev);
		return PCI_ERS_RESULT_NEED_RESET;
	case pci_channel_io_perm_failure:
		ipr_pci_perm_failure(pdev);
		return PCI_ERS_RESULT_DISCONNECT;
		break;
	default:
		break;
	}
	return PCI_ERS_RESULT_NEED_RESET;
}