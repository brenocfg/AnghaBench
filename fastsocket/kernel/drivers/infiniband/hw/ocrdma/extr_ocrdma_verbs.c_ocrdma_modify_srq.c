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
struct ocrdma_srq {int dummy; } ;
struct ib_udata {int dummy; } ;
struct ib_srq_attr {int dummy; } ;
struct ib_srq {int dummy; } ;
typedef  enum ib_srq_attr_mask { ____Placeholder_ib_srq_attr_mask } ib_srq_attr_mask ;

/* Variables and functions */
 int EINVAL ; 
 int IB_SRQ_MAX_WR ; 
 struct ocrdma_srq* get_ocrdma_srq (struct ib_srq*) ; 
 int ocrdma_mbx_modify_srq (struct ocrdma_srq*,struct ib_srq_attr*) ; 

int ocrdma_modify_srq(struct ib_srq *ibsrq,
		      struct ib_srq_attr *srq_attr,
		      enum ib_srq_attr_mask srq_attr_mask,
		      struct ib_udata *udata)
{
	int status = 0;
	struct ocrdma_srq *srq;

	srq = get_ocrdma_srq(ibsrq);
	if (srq_attr_mask & IB_SRQ_MAX_WR)
		status = -EINVAL;
	else
		status = ocrdma_mbx_modify_srq(srq, srq_attr);
	return status;
}