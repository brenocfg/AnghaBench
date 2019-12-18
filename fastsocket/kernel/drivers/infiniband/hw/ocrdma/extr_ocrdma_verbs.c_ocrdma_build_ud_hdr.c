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
struct ocrdma_qp {scalar_t__ qp_type; int /*<<< orphan*/  qkey; } ;
struct ocrdma_hdr_wqe {int dummy; } ;
struct ocrdma_ewqe_ud_hdr {int /*<<< orphan*/  rsvd_ahid; int /*<<< orphan*/  qkey; int /*<<< orphan*/  rsvd_dest_qpn; } ;
struct ocrdma_ah {int /*<<< orphan*/  id; } ;
struct TYPE_3__ {int /*<<< orphan*/  remote_qkey; int /*<<< orphan*/  remote_qpn; int /*<<< orphan*/  ah; } ;
struct TYPE_4__ {TYPE_1__ ud; } ;
struct ib_send_wr {TYPE_2__ wr; } ;

/* Variables and functions */
 scalar_t__ IB_QPT_GSI ; 
 struct ocrdma_ah* get_ocrdma_ah (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocrdma_build_ud_hdr(struct ocrdma_qp *qp,
				struct ocrdma_hdr_wqe *hdr,
				struct ib_send_wr *wr)
{
	struct ocrdma_ewqe_ud_hdr *ud_hdr =
		(struct ocrdma_ewqe_ud_hdr *)(hdr + 1);
	struct ocrdma_ah *ah = get_ocrdma_ah(wr->wr.ud.ah);

	ud_hdr->rsvd_dest_qpn = wr->wr.ud.remote_qpn;
	if (qp->qp_type == IB_QPT_GSI)
		ud_hdr->qkey = qp->qkey;
	else
		ud_hdr->qkey = wr->wr.ud.remote_qkey;
	ud_hdr->rsvd_ahid = ah->id;
}