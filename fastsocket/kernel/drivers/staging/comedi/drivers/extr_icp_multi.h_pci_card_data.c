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
struct pcilst_struct {unsigned char pci_bus; unsigned char pci_slot; unsigned char pci_func; unsigned int irq; int /*<<< orphan*/ * io_addr; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */

__attribute__((used)) static int pci_card_data(struct pcilst_struct *inova,
			 unsigned char *pci_bus, unsigned char *pci_slot,
			 unsigned char *pci_func, resource_size_t * io_addr,
			 unsigned int *irq)
{
	int i;

	if (!inova)
		return -1;
	*pci_bus = inova->pci_bus;
	*pci_slot = inova->pci_slot;
	*pci_func = inova->pci_func;
	for (i = 0; i < 5; i++)
		io_addr[i] = inova->io_addr[i];
	*irq = inova->irq;
	return 0;
}