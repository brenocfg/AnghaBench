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
typedef  scalar_t__ u8 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int K_BCM1480_INT_PCI_INTA ; 

int pcibios_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	if (pin == 0)
		return -1;

	return K_BCM1480_INT_PCI_INTA - 1 + pin;
}