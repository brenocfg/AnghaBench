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
struct pcilst_struct {int used; int /*<<< orphan*/  pcidev; int /*<<< orphan*/ * io_addr; } ;

/* Variables and functions */
 scalar_t__ comedi_pci_enable (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 

int pci_card_alloc(struct pcilst_struct *amcc, int master)
{
	int i;

	if (!amcc)
		return -1;

	if (amcc->used)
		return 1;
	if (comedi_pci_enable(amcc->pcidev, "addi_amcc_s5933"))
		return -1;
	/* Resources will be accurate now. */
	for (i = 0; i < 5; i++)
		amcc->io_addr[i] = pci_resource_start(amcc->pcidev, i);
	if (master)
		pci_set_master(amcc->pcidev);
	amcc->used = 1;

	return 0;
}