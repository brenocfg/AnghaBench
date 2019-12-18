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
struct oxu_hcd {int* qh_used; int /*<<< orphan*/  mem_lock; TYPE_1__* mem; } ;
struct ehci_qh {int /*<<< orphan*/ * dummy; int /*<<< orphan*/  qtd_list; int /*<<< orphan*/  qh_dma; struct oxu_hcd* oxu; int /*<<< orphan*/  kref; } ;
struct TYPE_2__ {int /*<<< orphan*/ * qh_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int QHEAD_NUM ; 
 int /*<<< orphan*/ * ehci_qtd_alloc (struct oxu_hcd*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ehci_qh*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oxu_dbg (struct oxu_hcd*,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virt_to_phys (struct ehci_qh*) ; 

__attribute__((used)) static struct ehci_qh *oxu_qh_alloc(struct oxu_hcd *oxu)
{
	int i;
	struct ehci_qh *qh = NULL;

	spin_lock(&oxu->mem_lock);

	for (i = 0; i < QHEAD_NUM; i++)
		if (!oxu->qh_used[i])
			break;

	if (i < QHEAD_NUM) {
		qh = (struct ehci_qh *) &oxu->mem->qh_pool[i];
		memset(qh, 0, sizeof *qh);

		kref_init(&qh->kref);
		qh->oxu = oxu;
		qh->qh_dma = virt_to_phys(qh);
		INIT_LIST_HEAD(&qh->qtd_list);

		/* dummy td enables safe urb queuing */
		qh->dummy = ehci_qtd_alloc(oxu);
		if (qh->dummy == NULL) {
			oxu_dbg(oxu, "no dummy td\n");
			oxu->qh_used[i] = 0;

			return NULL;
		}

		oxu->qh_used[i] = 1;
	}

	spin_unlock(&oxu->mem_lock);

	return qh;
}