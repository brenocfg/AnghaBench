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
struct pci_dev_rh1 {scalar_t__ __aer_firmware_first_valid; } ;
struct pci_dev {int aer_firmware_first; struct pci_dev_rh1* rh_reserved1; } ;

/* Variables and functions */

__attribute__((used)) static inline int pcie_aer_get_firmware_first(struct pci_dev *pci_dev)
{
	struct pci_dev_rh1 *pdr = pci_dev->rh_reserved1;

	if (pdr && pdr->__aer_firmware_first_valid)
		return pci_dev->aer_firmware_first;
	return 0;
}