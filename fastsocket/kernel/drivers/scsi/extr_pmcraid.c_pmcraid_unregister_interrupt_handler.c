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
struct pmcraid_instance {int num_hrrq; scalar_t__ interrupt_mode; int /*<<< orphan*/  pdev; TYPE_1__* hrrq_vector; } ;
struct TYPE_2__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pci_disable_msix (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void pmcraid_unregister_interrupt_handler(struct pmcraid_instance *pinstance)
{
	int i;

	for (i = 0; i < pinstance->num_hrrq; i++)
		free_irq(pinstance->hrrq_vector[i].vector,
			 &(pinstance->hrrq_vector[i]));

	if (pinstance->interrupt_mode) {
		pci_disable_msix(pinstance->pdev);
		pinstance->interrupt_mode = 0;
	}
}