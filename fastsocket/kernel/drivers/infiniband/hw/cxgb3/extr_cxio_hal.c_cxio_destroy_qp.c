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
typedef  union t3_wr {int dummy; } t3_wr ;
struct t3_wq {unsigned long size_log2; unsigned long rq_size_log2; int /*<<< orphan*/  qpid; int /*<<< orphan*/  rq; int /*<<< orphan*/  rq_addr; int /*<<< orphan*/  sq; int /*<<< orphan*/  queue; } ;
struct cxio_ucontext {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct cxio_rdev {TYPE_2__ rnic_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxio_hal_rqtpool_free (struct cxio_rdev*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping ; 
 int /*<<< orphan*/  pci_unmap_addr (struct t3_wq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_qpid (struct cxio_rdev*,int /*<<< orphan*/ ,struct cxio_ucontext*) ; 

int cxio_destroy_qp(struct cxio_rdev *rdev_p, struct t3_wq *wq,
		    struct cxio_ucontext *uctx)
{
	dma_free_coherent(&(rdev_p->rnic_info.pdev->dev),
			  (1UL << (wq->size_log2))
			  * sizeof(union t3_wr), wq->queue,
			  pci_unmap_addr(wq, mapping));
	kfree(wq->sq);
	cxio_hal_rqtpool_free(rdev_p, wq->rq_addr, (1UL << wq->rq_size_log2));
	kfree(wq->rq);
	put_qpid(rdev_p, wq->qpid, uctx);
	return 0;
}