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
struct ehci_qh_hw {int dummy; } ;
struct ehci_qh {int refcount; int /*<<< orphan*/  qh_dma; struct ehci_qh_hw* hw; int /*<<< orphan*/ * dummy; int /*<<< orphan*/  qtd_list; struct ehci_hcd* ehci; } ;
struct ehci_hcd {int /*<<< orphan*/  qh_pool; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct ehci_qh_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehci_dbg (struct ehci_hcd*,char*) ; 
 int /*<<< orphan*/ * ehci_qtd_alloc (struct ehci_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ehci_qh*) ; 
 struct ehci_qh* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ehci_qh_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ehci_qh *ehci_qh_alloc (struct ehci_hcd *ehci, gfp_t flags)
{
	struct ehci_qh		*qh;
	dma_addr_t		dma;

	qh = kzalloc(sizeof *qh, GFP_ATOMIC);
	if (!qh)
		goto done;
	qh->hw = (struct ehci_qh_hw *)
		dma_pool_alloc(ehci->qh_pool, flags, &dma);
	if (!qh->hw)
		goto fail;
	memset(qh->hw, 0, sizeof *qh->hw);
	qh->refcount = 1;
	qh->ehci = ehci;
	qh->qh_dma = dma;
	// INIT_LIST_HEAD (&qh->qh_list);
	INIT_LIST_HEAD (&qh->qtd_list);

	/* dummy td enables safe urb queuing */
	qh->dummy = ehci_qtd_alloc (ehci, flags);
	if (qh->dummy == NULL) {
		ehci_dbg (ehci, "no dummy td\n");
		goto fail1;
	}
done:
	return qh;
fail1:
	dma_pool_free(ehci->qh_pool, qh->hw, qh->qh_dma);
fail:
	kfree(qh);
	return NULL;
}