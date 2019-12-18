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
struct trace_seq {int dummy; } ;
struct pci_driver {int /*<<< orphan*/  name; } ;
struct pci_dev {TYPE_2__* resource; int /*<<< orphan*/  irq; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
typedef  int resource_size_t ;
struct TYPE_4__ {int flags; scalar_t__ start; scalar_t__ end; } ;
struct TYPE_3__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int PCI_REGION_FLAG_MASK ; 
 struct pci_driver* pci_dev_driver (struct pci_dev const*) ; 
 int /*<<< orphan*/  pci_resource_to_user (struct pci_dev const*,int,TYPE_2__*,int*,int*) ; 
 scalar_t__ trace_seq_printf (struct trace_seq*,char*,...) ; 

__attribute__((used)) static int mmio_print_pcidev(struct trace_seq *s, const struct pci_dev *dev)
{
	int ret = 0;
	int i;
	resource_size_t start, end;
	const struct pci_driver *drv = pci_dev_driver(dev);

	/* XXX: incomplete checks for trace_seq_printf() return value */
	ret += trace_seq_printf(s, "PCIDEV %02x%02x %04x%04x %x",
				dev->bus->number, dev->devfn,
				dev->vendor, dev->device, dev->irq);
	/*
	 * XXX: is pci_resource_to_user() appropriate, since we are
	 * supposed to interpret the __ioremap() phys_addr argument based on
	 * these printed values?
	 */
	for (i = 0; i < 7; i++) {
		pci_resource_to_user(dev, i, &dev->resource[i], &start, &end);
		ret += trace_seq_printf(s, " %llx",
			(unsigned long long)(start |
			(dev->resource[i].flags & PCI_REGION_FLAG_MASK)));
	}
	for (i = 0; i < 7; i++) {
		pci_resource_to_user(dev, i, &dev->resource[i], &start, &end);
		ret += trace_seq_printf(s, " %llx",
			dev->resource[i].start < dev->resource[i].end ?
			(unsigned long long)(end - start) + 1 : 0);
	}
	if (drv)
		ret += trace_seq_printf(s, " %s\n", drv->name);
	else
		ret += trace_seq_printf(s, " \n");
	return ret;
}