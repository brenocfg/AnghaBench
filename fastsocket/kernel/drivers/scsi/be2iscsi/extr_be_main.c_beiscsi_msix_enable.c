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
struct beiscsi_hba {int num_cpus; int msix_enabled; TYPE_1__* msix_entries; int /*<<< orphan*/  pcidev; } ;
struct TYPE_2__ {int entry; } ;

/* Variables and functions */
 int pci_enable_msix (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static void beiscsi_msix_enable(struct beiscsi_hba *phba)
{
	int i, status;

	for (i = 0; i <= phba->num_cpus; i++)
		phba->msix_entries[i].entry = i;

	status = pci_enable_msix(phba->pcidev, phba->msix_entries,
				 (phba->num_cpus + 1));
	if (!status)
		phba->msix_enabled = true;

	return;
}