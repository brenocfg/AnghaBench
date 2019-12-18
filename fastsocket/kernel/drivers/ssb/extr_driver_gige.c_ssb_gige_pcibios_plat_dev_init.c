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
struct TYPE_4__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; int /*<<< orphan*/  name; } ;
struct ssb_gige {TYPE_2__ mem_resource; int /*<<< orphan*/  pci_ops; } ;
struct ssb_device {int dummy; } ;
struct resource {int flags; int /*<<< orphan*/  end; int /*<<< orphan*/  start; int /*<<< orphan*/  name; } ;
struct pci_dev {scalar_t__ irq; struct resource* resource; TYPE_1__* bus; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int ENODEV ; 
 int IORESOURCE_MEM ; 
 int IORESOURCE_PCI_FIXED ; 
 int /*<<< orphan*/  PCI_INTERRUPT_LINE ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct ssb_gige* ssb_get_drvdata (struct ssb_device*) ; 
 scalar_t__ ssb_mips_irq (struct ssb_device*) ; 

int ssb_gige_pcibios_plat_dev_init(struct ssb_device *sdev,
				   struct pci_dev *pdev)
{
	struct ssb_gige *dev = ssb_get_drvdata(sdev);
	struct resource *res;

	if (pdev->bus->ops != &dev->pci_ops) {
		/* The PCI device is not on this SSB GigE bridge device. */
		return -ENODEV;
	}

	/* Fixup the PCI resources. */
	res = &(pdev->resource[0]);
	res->flags = IORESOURCE_MEM | IORESOURCE_PCI_FIXED;
	res->name = dev->mem_resource.name;
	res->start = dev->mem_resource.start;
	res->end = dev->mem_resource.end;

	/* Fixup interrupt lines. */
	pdev->irq = ssb_mips_irq(sdev) + 2;
	pci_write_config_byte(pdev, PCI_INTERRUPT_LINE, pdev->irq);

	return 0;
}