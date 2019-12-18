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
struct pci_dev {scalar_t__ device; } ;
struct TYPE_2__ {scalar_t__ device_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ANY_ID ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_DT ; 
 TYPE_1__* dt3k_boardtypes ; 
 int n_dt3k_boards ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  printk (char*,scalar_t__) ; 

__attribute__((used)) static struct pci_dev *dt_pci_find_device(struct pci_dev *from, int *board)
{
	int i;

	for (from = pci_get_device(PCI_VENDOR_ID_DT, PCI_ANY_ID, from);
	     from != NULL;
	     from = pci_get_device(PCI_VENDOR_ID_DT, PCI_ANY_ID, from)) {
		for (i = 0; i < n_dt3k_boards; i++) {
			if (from->device == dt3k_boardtypes[i].device_id) {
				*board = i;
				return from;
			}
		}
		printk
		    ("unknown Data Translation PCI device found with device_id=0x%04x\n",
		     from->device);
	}
	*board = -1;
	return from;
}