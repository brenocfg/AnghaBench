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
struct TYPE_2__ {scalar_t__ ptr; } ;
struct ehci_qh {int /*<<< orphan*/  qh_dma; int /*<<< orphan*/  hw; scalar_t__ dummy; TYPE_1__ qh_next; int /*<<< orphan*/  qtd_list; struct ehci_hcd* ehci; } ;
struct ehci_hcd {int /*<<< orphan*/  qh_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehci_dbg (struct ehci_hcd*,char*) ; 
 int /*<<< orphan*/  ehci_qtd_free (struct ehci_hcd*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct ehci_qh*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qh_destroy(struct ehci_qh *qh)
{
	struct ehci_hcd *ehci = qh->ehci;

	/* clean qtds first, and know this is not linked */
	if (!list_empty (&qh->qtd_list) || qh->qh_next.ptr) {
		ehci_dbg (ehci, "unused qh not empty!\n");
		BUG ();
	}
	if (qh->dummy)
		ehci_qtd_free (ehci, qh->dummy);
	dma_pool_free(ehci->qh_pool, qh->hw, qh->qh_dma);
	kfree(qh);
}