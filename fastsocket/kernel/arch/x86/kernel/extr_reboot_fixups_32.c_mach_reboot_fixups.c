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
struct device_fixup {int /*<<< orphan*/  (* reboot_fixup ) (struct pci_dev*) ;int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct device_fixup*) ; 
 struct device_fixup* fixups_table ; 
 scalar_t__ in_interrupt () ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct pci_dev*) ; 

void mach_reboot_fixups(void)
{
	const struct device_fixup *cur;
	struct pci_dev *dev;
	int i;

	/* we can be called from sysrq-B code. In such a case it is
	 * prohibited to dig PCI */
	if (in_interrupt())
		return;

	for (i=0; i < ARRAY_SIZE(fixups_table); i++) {
		cur = &(fixups_table[i]);
		dev = pci_get_device(cur->vendor, cur->device, NULL);
		if (!dev)
			continue;

		cur->reboot_fixup(dev);
	}
}