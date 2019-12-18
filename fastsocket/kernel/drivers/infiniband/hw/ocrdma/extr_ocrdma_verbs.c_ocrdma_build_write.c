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
struct ocrdma_hdr_wqe {int /*<<< orphan*/  total_len; } ;
struct TYPE_3__ {int /*<<< orphan*/  rkey; int /*<<< orphan*/  remote_addr; } ;
struct TYPE_4__ {TYPE_1__ rdma; } ;
struct ib_send_wr {TYPE_2__ wr; } ;

/* Variables and functions */
 int ocrdma_build_inline_sges (struct ocrdma_qp*,struct ocrdma_hdr_wqe*,struct ocrdma_sge*,struct ib_send_wr*,int) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocrdma_build_write(struct ocrdma_qp *qp, struct ocrdma_hdr_wqe *hdr,
			      struct ib_send_wr *wr)
{
	int status;
	struct ocrdma_sge *ext_rw = (struct ocrdma_sge *)(hdr + 1);
	struct ocrdma_sge *sge = ext_rw + 1;
	u32 wqe_size = sizeof(*hdr) + sizeof(*ext_rw);

	status = ocrdma_build_inline_sges(qp, hdr, sge, wr, wqe_size);
	if (status)
		return status;
	ext_rw->addr_lo = wr->wr.rdma.remote_addr;
	ext_rw->addr_hi = upper_32_bits(wr->wr.rdma.remote_addr);
	ext_rw->lrkey = wr->wr.rdma.rkey;
	ext_rw->len = hdr->total_len;
	return 0;
}