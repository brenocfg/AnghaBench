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
struct svcxprt_rdma {scalar_t__ sc_dma_lkey; TYPE_1__* sc_cm_id; int /*<<< orphan*/  sc_dma_used; } ;
struct svc_rdma_op_ctxt {int count; int /*<<< orphan*/  direction; TYPE_2__* sge; struct svcxprt_rdma* xprt; } ;
struct TYPE_4__ {scalar_t__ lkey; scalar_t__ length; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void svc_rdma_unmap_dma(struct svc_rdma_op_ctxt *ctxt)
{
	struct svcxprt_rdma *xprt = ctxt->xprt;
	int i;
	for (i = 0; i < ctxt->count && ctxt->sge[i].length; i++) {
		/*
		 * Unmap the DMA addr in the SGE if the lkey matches
		 * the sc_dma_lkey, otherwise, ignore it since it is
		 * an FRMR lkey and will be unmapped later when the
		 * last WR that uses it completes.
		 */
		if (ctxt->sge[i].lkey == xprt->sc_dma_lkey) {
			atomic_dec(&xprt->sc_dma_used);
			ib_dma_unmap_page(xprt->sc_cm_id->device,
					    ctxt->sge[i].addr,
					    ctxt->sge[i].length,
					    ctxt->direction);
		}
	}
}