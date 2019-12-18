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
struct sge_fl {unsigned int avail; size_t pidx; size_t size; unsigned int pend_cred; scalar_t__ cntxt_id; int /*<<< orphan*/ * desc; struct rx_sw_desc* sdesc; int /*<<< orphan*/  alloc_failed; int /*<<< orphan*/  large_alloc_failed; } ;
struct rx_sw_desc {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  starving_fl; scalar_t__ egr_start; } ;
struct adapter {TYPE_1__ sge; int /*<<< orphan*/  pdev_dev; } ;
typedef  int gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int FL_PG_ORDER ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  RX_LARGE_BUF ; 
 int __GFP_COLD ; 
 int __GFP_COMP ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  __free_pages (struct page*,int) ; 
 struct page* alloc_page (int) ; 
 struct page* alloc_pages (int,int) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fl_starving (struct sge_fl*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  ring_fl_db (struct adapter*,struct sge_fl*) ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_rx_sw_desc (struct rx_sw_desc*,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int refill_fl(struct adapter *adap, struct sge_fl *q, int n,
			      gfp_t gfp)
{
	struct page *pg;
	dma_addr_t mapping;
	unsigned int cred = q->avail;
	__be64 *d = &q->desc[q->pidx];
	struct rx_sw_desc *sd = &q->sdesc[q->pidx];

	gfp |= __GFP_NOWARN | __GFP_COLD;

#if FL_PG_ORDER > 0
	/*
	 * Prefer large buffers
	 */
	while (n) {
		pg = alloc_pages(gfp | __GFP_COMP, FL_PG_ORDER);
		if (unlikely(!pg)) {
			q->large_alloc_failed++;
			break;       /* fall back to single pages */
		}

		mapping = dma_map_page(adap->pdev_dev, pg, 0,
				       PAGE_SIZE << FL_PG_ORDER,
				       PCI_DMA_FROMDEVICE);
		if (unlikely(dma_mapping_error(adap->pdev_dev, mapping))) {
			__free_pages(pg, FL_PG_ORDER);
			goto out;   /* do not try small pages for this error */
		}
		mapping |= RX_LARGE_BUF;
		*d++ = cpu_to_be64(mapping);

		set_rx_sw_desc(sd, pg, mapping);
		sd++;

		q->avail++;
		if (++q->pidx == q->size) {
			q->pidx = 0;
			sd = q->sdesc;
			d = q->desc;
		}
		n--;
	}
#endif

	while (n--) {
		pg = alloc_page(gfp);
		if (unlikely(!pg)) {
			q->alloc_failed++;
			break;
		}

		mapping = dma_map_page(adap->pdev_dev, pg, 0, PAGE_SIZE,
				       PCI_DMA_FROMDEVICE);
		if (unlikely(dma_mapping_error(adap->pdev_dev, mapping))) {
			put_page(pg);
			goto out;
		}
		*d++ = cpu_to_be64(mapping);

		set_rx_sw_desc(sd, pg, mapping);
		sd++;

		q->avail++;
		if (++q->pidx == q->size) {
			q->pidx = 0;
			sd = q->sdesc;
			d = q->desc;
		}
	}

out:	cred = q->avail - cred;
	q->pend_cred += cred;
	ring_fl_db(adap, q);

	if (unlikely(fl_starving(q))) {
		smp_wmb();
		set_bit(q->cntxt_id - adap->sge.egr_start,
			adap->sge.starving_fl);
	}

	return cred;
}