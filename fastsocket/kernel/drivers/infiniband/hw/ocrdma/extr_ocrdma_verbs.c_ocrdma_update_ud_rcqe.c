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
struct TYPE_2__ {int /*<<< orphan*/  rxlen_pkey; } ;
struct ocrdma_cqe {TYPE_1__ ud; int /*<<< orphan*/  flags_status_srcqpn; } ;
struct ib_wc {int src_qp; int pkey_index; int byte_len; int /*<<< orphan*/  wc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WC_GRH ; 
 int OCRDMA_CQE_PKEY_MASK ; 
 int OCRDMA_CQE_SRCQP_MASK ; 
 int OCRDMA_CQE_UD_STATUS_MASK ; 
 int OCRDMA_CQE_UD_STATUS_SHIFT ; 
 int OCRDMA_CQE_UD_XFER_LEN_SHIFT ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocrdma_update_ud_rcqe(struct ib_wc *ibwc, struct ocrdma_cqe *cqe)
{
	int status;

	status = (le32_to_cpu(cqe->flags_status_srcqpn) &
		OCRDMA_CQE_UD_STATUS_MASK) >> OCRDMA_CQE_UD_STATUS_SHIFT;
	ibwc->src_qp = le32_to_cpu(cqe->flags_status_srcqpn) &
						OCRDMA_CQE_SRCQP_MASK;
	ibwc->pkey_index = le32_to_cpu(cqe->ud.rxlen_pkey) &
						OCRDMA_CQE_PKEY_MASK;
	ibwc->wc_flags = IB_WC_GRH;
	ibwc->byte_len = (le32_to_cpu(cqe->ud.rxlen_pkey) >>
					OCRDMA_CQE_UD_XFER_LEN_SHIFT);
	return status;
}