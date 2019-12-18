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
struct pcilst_struct {int /*<<< orphan*/  pcidev; scalar_t__ used; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_pci_disable (int /*<<< orphan*/ ) ; 

int i_pci_card_free(struct pcilst_struct *amcc)
{
	if (!amcc)
		return -1;

	if (!amcc->used)
		return 1;
	amcc->used = 0;
	comedi_pci_disable(amcc->pcidev);
	return 0;
}