#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct pci_driver {unsigned long long name; } ;
struct pci_dev {TYPE_2__* resource; int /*<<< orphan*/  irq; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
typedef  int resource_size_t ;
struct TYPE_4__ {int flags; scalar_t__ start; scalar_t__ end; } ;
struct TYPE_3__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int PCI_REGION_FLAG_MASK ; 
 int PCI_ROM_RESOURCE ; 
 struct pci_driver* pci_dev_driver (struct pci_dev const*) ; 
 int /*<<< orphan*/  pci_resource_to_user (struct pci_dev const*,int,TYPE_2__*,int*,int*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned long long,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 

__attribute__((used)) static int show_device(struct seq_file *m, void *v)
{
	const struct pci_dev *dev = v;
	const struct pci_driver *drv;
	int i;

	if (dev == NULL)
		return 0;

	drv = pci_dev_driver(dev);
	seq_printf(m, "%02x%02x\t%04x%04x\t%x",
			dev->bus->number,
			dev->devfn,
			dev->vendor,
			dev->device,
			dev->irq);

	/* only print standard and ROM resources to preserve compatibility */
	for (i = 0; i <= PCI_ROM_RESOURCE; i++) {
		resource_size_t start, end;
		pci_resource_to_user(dev, i, &dev->resource[i], &start, &end);
		seq_printf(m, "\t%16llx",
			(unsigned long long)(start |
			(dev->resource[i].flags & PCI_REGION_FLAG_MASK)));
	}
	for (i = 0; i <= PCI_ROM_RESOURCE; i++) {
		resource_size_t start, end;
		pci_resource_to_user(dev, i, &dev->resource[i], &start, &end);
		seq_printf(m, "\t%16llx",
			dev->resource[i].start < dev->resource[i].end ?
			(unsigned long long)(end - start) + 1 : 0);
	}
	seq_putc(m, '\t');
	if (drv)
		seq_printf(m, "%s", drv->name);
	seq_putc(m, '\n');
	return 0;
}