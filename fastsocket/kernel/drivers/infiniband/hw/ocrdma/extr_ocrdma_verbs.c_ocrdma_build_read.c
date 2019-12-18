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
typedef  int u32 ;
struct ocrdma_sge {int /*<<< orphan*/  len; int /*<<< orphan*/  lrkey; int /*<<< orphan*/  addr_hi; int /*<<< orphan*/  addr_lo; } ;
struct ocrdma_qp {int dummy; } ;
struct ocrdma_hdr_wqe {int cw; int /*<<< orphan*/  total_len; } ;
struct TYPE_3__ {int /*<<< orphan*/  rkey; int /*<<< orphan*/  remote_addr; } ;
struct TYPE_4__ {TYPE_1__ rdma; } ;
struct ib_send_wr {TYPE_2__ wr; int /*<<< orphan*/  sg_list; int /*<<< orphan*/  num_sge; } ;

/* Variables and functions */
 int OCRDMA_READ ; 
 int OCRDMA_TYPE_LKEY ; 
 int OCRDMA_WQE_OPCODE_SHIFT ; 
 int OCRDMA_WQE_SIZE_SHIFT ; 
 int OCRDMA_WQE_STRIDE ; 
 int OCRDMA_WQE_TYPE_SHIFT ; 
 int /*<<< orphan*/  ocrdma_build_sges (struct ocrdma_hdr_wqe*,struct ocrdma_sge*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocrdma_build_read(struct ocrdma_qp *qp, struct ocrdma_hdr_wqe *hdr,
			      struct ib_send_wr *wr)
{
	struct ocrdma_sge *ext_rw = (struct ocrdma_sge *)(hdr + 1);
	struct ocrdma_sge *sge = ext_rw + 1;
	u32 wqe_size = ((wr->num_sge + 1) * sizeof(struct ocrdma_sge)) +
	    sizeof(struct ocrdma_hdr_wqe);

	ocrdma_build_sges(hdr, sge, wr->num_sge, wr->sg_list);
	hdr->cw |= ((wqe_size / OCRDMA_WQE_STRIDE) << OCRDMA_WQE_SIZE_SHIFT);
	hdr->cw |= (OCRDMA_READ << OCRDMA_WQE_OPCODE_SHIFT);
	hdr->cw |= (OCRDMA_TYPE_LKEY << OCRDMA_WQE_TYPE_SHIFT);

	ext_rw->addr_lo = wr->wr.rdma.remote_addr;
	ext_rw->addr_hi = upper_32_bits(wr->wr.rdma.remote_addr);
	ext_rw->lrkey = wr->wr.rdma.rkey;
	ext_rw->len = hdr->total_len;
}