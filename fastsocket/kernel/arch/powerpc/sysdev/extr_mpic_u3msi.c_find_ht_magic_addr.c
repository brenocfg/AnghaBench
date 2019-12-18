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
typedef  int /*<<< orphan*/  u64 ;
struct pci_dev {struct pci_bus* bus; } ;
struct pci_bus {int /*<<< orphan*/  self; struct pci_bus* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  HT_CAPTYPE_MSI_MAPPING ; 
 unsigned int pci_find_ht_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_ht_magic_addr (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static u64 find_ht_magic_addr(struct pci_dev *pdev)
{
	struct pci_bus *bus;
	unsigned int pos;

	for (bus = pdev->bus; bus; bus = bus->parent) {
		pos = pci_find_ht_capability(bus->self, HT_CAPTYPE_MSI_MAPPING);
		if (pos)
			return read_ht_magic_addr(bus->self, pos);
	}

	return 0;
}