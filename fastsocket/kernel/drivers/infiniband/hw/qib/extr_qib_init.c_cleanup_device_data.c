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
struct qib_devdata {int num_pports; int cfgctxts; int rcvtidcnt; int ctxtcnt; struct qib_ctxtdata** boardname; int /*<<< orphan*/  uctxt_lock; struct qib_ctxtdata** rcd; struct page** pageshadow; TYPE_2__* pcidev; int /*<<< orphan*/ * physshadow; int /*<<< orphan*/ * pioavailregs_dma; int /*<<< orphan*/  pioavailregs_phys; TYPE_1__* pport; } ;
struct qib_ctxtdata {int dummy; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  cc_shadow_lock; struct qib_ctxtdata** congestion_entries_shadow; struct qib_ctxtdata** ccti_entries_shadow; struct qib_ctxtdata** ccti_entries; struct qib_ctxtdata** congestion_entries; int /*<<< orphan*/ * statusp; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  QIB_STATUS_CHIP_PRESENT ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qib_ctxtdata**) ; 
 int /*<<< orphan*/  pci_unmap_page (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_disable_wc (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_free_ctxtdata (struct qib_devdata*,struct qib_ctxtdata*) ; 
 int /*<<< orphan*/  qib_release_user_pages (struct page**,int) ; 
 int /*<<< orphan*/  qib_wc_pat ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vfree (struct page**) ; 

__attribute__((used)) static void cleanup_device_data(struct qib_devdata *dd)
{
	int ctxt;
	int pidx;
	struct qib_ctxtdata **tmp;
	unsigned long flags;

	/* users can't do anything more with chip */
	for (pidx = 0; pidx < dd->num_pports; ++pidx) {
		if (dd->pport[pidx].statusp)
			*dd->pport[pidx].statusp &= ~QIB_STATUS_CHIP_PRESENT;

		spin_lock(&dd->pport[pidx].cc_shadow_lock);

		kfree(dd->pport[pidx].congestion_entries);
		dd->pport[pidx].congestion_entries = NULL;
		kfree(dd->pport[pidx].ccti_entries);
		dd->pport[pidx].ccti_entries = NULL;
		kfree(dd->pport[pidx].ccti_entries_shadow);
		dd->pport[pidx].ccti_entries_shadow = NULL;
		kfree(dd->pport[pidx].congestion_entries_shadow);
		dd->pport[pidx].congestion_entries_shadow = NULL;

		spin_unlock(&dd->pport[pidx].cc_shadow_lock);
	}

	if (!qib_wc_pat)
		qib_disable_wc(dd);

	if (dd->pioavailregs_dma) {
		dma_free_coherent(&dd->pcidev->dev, PAGE_SIZE,
				  (void *) dd->pioavailregs_dma,
				  dd->pioavailregs_phys);
		dd->pioavailregs_dma = NULL;
	}

	if (dd->pageshadow) {
		struct page **tmpp = dd->pageshadow;
		dma_addr_t *tmpd = dd->physshadow;
		int i, cnt = 0;

		for (ctxt = 0; ctxt < dd->cfgctxts; ctxt++) {
			int ctxt_tidbase = ctxt * dd->rcvtidcnt;
			int maxtid = ctxt_tidbase + dd->rcvtidcnt;

			for (i = ctxt_tidbase; i < maxtid; i++) {
				if (!tmpp[i])
					continue;
				pci_unmap_page(dd->pcidev, tmpd[i],
					       PAGE_SIZE, PCI_DMA_FROMDEVICE);
				qib_release_user_pages(&tmpp[i], 1);
				tmpp[i] = NULL;
				cnt++;
			}
		}

		tmpp = dd->pageshadow;
		dd->pageshadow = NULL;
		vfree(tmpp);
	}

	/*
	 * Free any resources still in use (usually just kernel contexts)
	 * at unload; we do for ctxtcnt, because that's what we allocate.
	 * We acquire lock to be really paranoid that rcd isn't being
	 * accessed from some interrupt-related code (that should not happen,
	 * but best to be sure).
	 */
	spin_lock_irqsave(&dd->uctxt_lock, flags);
	tmp = dd->rcd;
	dd->rcd = NULL;
	spin_unlock_irqrestore(&dd->uctxt_lock, flags);
	for (ctxt = 0; tmp && ctxt < dd->ctxtcnt; ctxt++) {
		struct qib_ctxtdata *rcd = tmp[ctxt];

		tmp[ctxt] = NULL; /* debugging paranoia */
		qib_free_ctxtdata(dd, rcd);
	}
	kfree(tmp);
	kfree(dd->boardname);
}