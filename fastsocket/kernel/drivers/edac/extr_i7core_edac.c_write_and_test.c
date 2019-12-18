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
typedef  scalar_t__ const u32 ;
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugf0 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,scalar_t__ const) ; 
 int /*<<< orphan*/  i7core_printk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,scalar_t__ const,scalar_t__ const) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int const,scalar_t__ const*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int const,scalar_t__ const) ; 

__attribute__((used)) static int write_and_test(struct pci_dev *dev, const int where, const u32 val)
{
	u32 read;
	int count;

	debugf0("setting pci %02x:%02x.%x reg=%02x value=%08x\n",
		dev->bus->number, PCI_SLOT(dev->devfn), PCI_FUNC(dev->devfn),
		where, val);

	for (count = 0; count < 10; count++) {
		if (count)
			msleep(100);
		pci_write_config_dword(dev, where, val);
		pci_read_config_dword(dev, where, &read);

		if (read == val)
			return 0;
	}

	i7core_printk(KERN_ERR, "Error during set pci %02x:%02x.%x reg=%02x "
		"write=%08x. Read=%08x\n",
		dev->bus->number, PCI_SLOT(dev->devfn), PCI_FUNC(dev->devfn),
		where, val, read);

	return -EINVAL;
}