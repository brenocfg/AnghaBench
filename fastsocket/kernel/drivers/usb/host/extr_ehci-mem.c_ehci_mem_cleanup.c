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
typedef  int /*<<< orphan*/  u32 ;
struct ehci_hcd {int periodic_size; int /*<<< orphan*/ * pshadow; int /*<<< orphan*/ * periodic; int /*<<< orphan*/  periodic_dma; int /*<<< orphan*/ * sitd_pool; int /*<<< orphan*/ * itd_pool; int /*<<< orphan*/ * qh_pool; int /*<<< orphan*/ * qtd_pool; int /*<<< orphan*/ * dummy; int /*<<< orphan*/ * async; } ;
struct TYPE_3__ {int /*<<< orphan*/  controller; } ;
struct TYPE_4__ {TYPE_1__ self; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_2__* ehci_to_hcd (struct ehci_hcd*) ; 
 int /*<<< orphan*/  free_cached_lists (struct ehci_hcd*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qh_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ehci_mem_cleanup (struct ehci_hcd *ehci)
{
	free_cached_lists(ehci);
	if (ehci->async)
		qh_put (ehci->async);
	ehci->async = NULL;

	if (ehci->dummy)
		qh_put(ehci->dummy);
	ehci->dummy = NULL;

	/* DMA consistent memory and pools */
	if (ehci->qtd_pool)
		dma_pool_destroy (ehci->qtd_pool);
	ehci->qtd_pool = NULL;

	if (ehci->qh_pool) {
		dma_pool_destroy (ehci->qh_pool);
		ehci->qh_pool = NULL;
	}

	if (ehci->itd_pool)
		dma_pool_destroy (ehci->itd_pool);
	ehci->itd_pool = NULL;

	if (ehci->sitd_pool)
		dma_pool_destroy (ehci->sitd_pool);
	ehci->sitd_pool = NULL;

	if (ehci->periodic)
		dma_free_coherent (ehci_to_hcd(ehci)->self.controller,
			ehci->periodic_size * sizeof (u32),
			ehci->periodic, ehci->periodic_dma);
	ehci->periodic = NULL;

	/* shadow periodic table */
	kfree(ehci->pshadow);
	ehci->pshadow = NULL;
}