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
struct rds_ib_mr {unsigned int sg_len; int /*<<< orphan*/ * sg; scalar_t__ sg_dma_len; struct rds_ib_device* device; } ;
struct rds_ib_device {int /*<<< orphan*/  dev; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  ib_dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 struct page* sg_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __rds_ib_teardown_mr(struct rds_ib_mr *ibmr)
{
	struct rds_ib_device *rds_ibdev = ibmr->device;

	if (ibmr->sg_dma_len) {
		ib_dma_unmap_sg(rds_ibdev->dev,
				ibmr->sg, ibmr->sg_len,
				DMA_BIDIRECTIONAL);
		ibmr->sg_dma_len = 0;
	}

	/* Release the s/g list */
	if (ibmr->sg_len) {
		unsigned int i;

		for (i = 0; i < ibmr->sg_len; ++i) {
			struct page *page = sg_page(&ibmr->sg[i]);

			/* FIXME we need a way to tell a r/w MR
			 * from a r/o MR */
			BUG_ON(irqs_disabled());
			set_page_dirty(page);
			put_page(page);
		}
		kfree(ibmr->sg);

		ibmr->sg = NULL;
		ibmr->sg_len = 0;
	}
}