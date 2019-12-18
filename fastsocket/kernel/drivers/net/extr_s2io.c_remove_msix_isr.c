#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct s2io_nic {int num_entries; int /*<<< orphan*/  pdev; TYPE_1__* s2io_entries; TYPE_1__* entries; } ;
struct TYPE_2__ {scalar_t__ in_use; int vector; void* arg; } ;

/* Variables and functions */
 scalar_t__ MSIX_REGISTERED_SUCCESS ; 
 int /*<<< orphan*/  free_irq (int,void*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_disable_msix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void remove_msix_isr(struct s2io_nic *sp)
{
	int i;
	u16 msi_control;

	for (i = 0; i < sp->num_entries; i++) {
		if (sp->s2io_entries[i].in_use == MSIX_REGISTERED_SUCCESS) {
			int vector = sp->entries[i].vector;
			void *arg = sp->s2io_entries[i].arg;
			free_irq(vector, arg);
		}
	}

	kfree(sp->entries);
	kfree(sp->s2io_entries);
	sp->entries = NULL;
	sp->s2io_entries = NULL;

	pci_read_config_word(sp->pdev, 0x42, &msi_control);
	msi_control &= 0xFFFE; /* Disable MSI */
	pci_write_config_word(sp->pdev, 0x42, msi_control);

	pci_disable_msix(sp->pdev);
}