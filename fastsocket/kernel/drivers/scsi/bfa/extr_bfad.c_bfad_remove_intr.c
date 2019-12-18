#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  vector; } ;
struct bfad_s {int bfad_flags; int nvec; TYPE_2__* pcidev; struct bfad_s* msix_tab; TYPE_1__ msix; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int BFAD_INTX_ON ; 
 int BFAD_MSIX_ON ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct bfad_s*) ; 
 int /*<<< orphan*/  pci_disable_msix (TYPE_2__*) ; 

void
bfad_remove_intr(struct bfad_s *bfad)
{
	int	i;

	if (bfad->bfad_flags & BFAD_MSIX_ON) {
		for (i = 0; i < bfad->nvec; i++)
			free_irq(bfad->msix_tab[i].msix.vector,
					&bfad->msix_tab[i]);

		pci_disable_msix(bfad->pcidev);
		bfad->bfad_flags &= ~BFAD_MSIX_ON;
	} else if (bfad->bfad_flags & BFAD_INTX_ON) {
		free_irq(bfad->pcidev->irq, bfad);
	}
}