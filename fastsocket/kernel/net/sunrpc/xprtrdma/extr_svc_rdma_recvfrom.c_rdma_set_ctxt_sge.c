#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct svcxprt_rdma {int /*<<< orphan*/  sc_dma_used; int /*<<< orphan*/  sc_dma_lkey; TYPE_1__* sc_cm_id; } ;
struct svc_rdma_op_ctxt {int count; TYPE_3__* sge; int /*<<< orphan*/  direction; } ;
struct svc_rdma_fastreg_mr {TYPE_2__* mr; } ;
struct kvec {scalar_t__ iov_len; scalar_t__ iov_base; } ;
struct TYPE_6__ {unsigned long addr; scalar_t__ length; int /*<<< orphan*/  lkey; } ;
struct TYPE_5__ {int /*<<< orphan*/  lkey; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EINVAL ; 
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 unsigned long ib_dma_map_page (int /*<<< orphan*/ ,scalar_t__,unsigned long,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_dma_mapping_error (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ virt_to_page (scalar_t__) ; 

__attribute__((used)) static int rdma_set_ctxt_sge(struct svcxprt_rdma *xprt,
			     struct svc_rdma_op_ctxt *ctxt,
			     struct svc_rdma_fastreg_mr *frmr,
			     struct kvec *vec,
			     u64 *sgl_offset,
			     int count)
{
	int i;
	unsigned long off;

	ctxt->count = count;
	ctxt->direction = DMA_FROM_DEVICE;
	for (i = 0; i < count; i++) {
		ctxt->sge[i].length = 0; /* in case map fails */
		if (!frmr) {
			BUG_ON(0 == virt_to_page(vec[i].iov_base));
			off = (unsigned long)vec[i].iov_base & ~PAGE_MASK;
			ctxt->sge[i].addr =
				ib_dma_map_page(xprt->sc_cm_id->device,
						virt_to_page(vec[i].iov_base),
						off,
						vec[i].iov_len,
						DMA_FROM_DEVICE);
			if (ib_dma_mapping_error(xprt->sc_cm_id->device,
						 ctxt->sge[i].addr))
				return -EINVAL;
			ctxt->sge[i].lkey = xprt->sc_dma_lkey;
			atomic_inc(&xprt->sc_dma_used);
		} else {
			ctxt->sge[i].addr = (unsigned long)vec[i].iov_base;
			ctxt->sge[i].lkey = frmr->mr->lkey;
		}
		ctxt->sge[i].length = vec[i].iov_len;
		*sgl_offset = *sgl_offset + vec[i].iov_len;
	}
	return 0;
}