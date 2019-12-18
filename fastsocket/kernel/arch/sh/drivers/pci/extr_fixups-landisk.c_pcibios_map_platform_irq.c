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
typedef  int u8 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,int,int) ; 

int pcibios_map_platform_irq(struct pci_dev *pdev, u8 slot, u8 pin)
{
	/*
	 * slot0: pin1-4 = irq5,6,7,8
	 * slot1: pin1-4 = irq6,7,8,5
	 * slot2: pin1-4 = irq7,8,5,6
	 * slot3: pin1-4 = irq8,5,6,7
	 */
	int irq = ((slot + pin - 1) & 0x3) + 5;

	if ((slot | (pin - 1)) > 0x3) {
		printk("PCI: Bad IRQ mapping request for slot %d pin %c\n",
		       slot, pin - 1 + 'A');
		return -1;
	}
	return irq;
}