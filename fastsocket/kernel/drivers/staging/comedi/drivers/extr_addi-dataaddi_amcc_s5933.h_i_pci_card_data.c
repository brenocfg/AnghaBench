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

int i_pci_card_data(struct pcilst_struct *amcc,
		    unsigned char *pci_bus, unsigned char *pci_slot,
		    unsigned char *pci_func, resource_size_t * io_addr,
		    unsigned int *irq)
{
	int i;

	if (!amcc)
		return -1;
	*pci_bus = amcc->pci_bus;
	*pci_slot = amcc->pci_slot;
	*pci_func = amcc->pci_func;
	for (i = 0; i < 5; i++)
		io_addr[i] = amcc->io_addr[i];
	*irq = amcc->irq;
	return 0;
}