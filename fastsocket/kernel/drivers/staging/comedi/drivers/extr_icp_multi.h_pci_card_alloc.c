#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcilst_struct {int used; TYPE_1__* pcidev; int /*<<< orphan*/  irq; int /*<<< orphan*/ * io_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ comedi_pci_enable (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  pci_resource_start (TYPE_1__*,int) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int pci_card_alloc(struct pcilst_struct *inova)
{
	int i;

	if (!inova) {
		printk(" - BUG!! inova is NULL!\n");
		return -1;
	}

	if (inova->used)
		return 1;
	if (comedi_pci_enable(inova->pcidev, "icp_multi")) {
		printk(" - Can't enable PCI device and request regions!\n");
		return -1;
	}
	/* Resources will be accurate now. */
	for (i = 0; i < 5; i++)
		inova->io_addr[i] = pci_resource_start(inova->pcidev, i);
	inova->irq = inova->pcidev->irq;
	inova->used = 1;
	return 0;
}