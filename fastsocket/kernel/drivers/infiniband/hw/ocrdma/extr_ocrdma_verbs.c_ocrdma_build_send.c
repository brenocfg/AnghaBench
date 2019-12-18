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
typedef  int u32 ;
struct ocrdma_sge {int dummy; } ;
struct ocrdma_qp {scalar_t__ qp_type; } ;
struct ocrdma_hdr_wqe {int dummy; } ;
struct ocrdma_ewqe_ud_hdr {int dummy; } ;
struct ib_send_wr {int dummy; } ;

/* Variables and functions */
 scalar_t__ IB_QPT_GSI ; 
 scalar_t__ IB_QPT_UD ; 
 int ocrdma_build_inline_sges (struct ocrdma_qp*,struct ocrdma_hdr_wqe*,struct ocrdma_sge*,struct ib_send_wr*,int) ; 
 int /*<<< orphan*/  ocrdma_build_ud_hdr (struct ocrdma_qp*,struct ocrdma_hdr_wqe*,struct ib_send_wr*) ; 

__attribute__((used)) static int ocrdma_build_send(struct ocrdma_qp *qp, struct ocrdma_hdr_wqe *hdr,
			     struct ib_send_wr *wr)
{
	int status;
	struct ocrdma_sge *sge;
	u32 wqe_size = sizeof(*hdr);

	if (qp->qp_type == IB_QPT_UD || qp->qp_type == IB_QPT_GSI) {
		ocrdma_build_ud_hdr(qp, hdr, wr);
		sge = (struct ocrdma_sge *)(hdr + 2);
		wqe_size += sizeof(struct ocrdma_ewqe_ud_hdr);
	} else
		sge = (struct ocrdma_sge *)(hdr + 1);

	status = ocrdma_build_inline_sges(qp, hdr, sge, wr, wqe_size);
	return status;
}