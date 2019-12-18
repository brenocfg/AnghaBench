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
typedef  int /*<<< orphan*/  u32 ;
struct ocrdma_qp {int cap_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCRDMA_CREATE_QP_REQ_BIND_MEMWIN_MASK ; 
 int /*<<< orphan*/  OCRDMA_CREATE_QP_REQ_FMR_EN_MASK ; 
 int /*<<< orphan*/  OCRDMA_CREATE_QP_REQ_INB_RDEN_MASK ; 
 int /*<<< orphan*/  OCRDMA_CREATE_QP_REQ_INB_WREN_MASK ; 
 int /*<<< orphan*/  OCRDMA_CREATE_QP_REQ_ZERO_LKEYEN_MASK ; 
 int OCRDMA_QP_FAST_REG ; 
 int OCRDMA_QP_INB_RD ; 
 int OCRDMA_QP_INB_WR ; 
 int OCRDMA_QP_LKEY0 ; 
 int OCRDMA_QP_MW_BIND ; 

__attribute__((used)) static u32 ocrdma_set_create_qp_mbx_access_flags(struct ocrdma_qp *qp)
{
	u32 flags = 0;
	if (qp->cap_flags & OCRDMA_QP_INB_RD)
		flags |= OCRDMA_CREATE_QP_REQ_INB_RDEN_MASK;
	if (qp->cap_flags & OCRDMA_QP_INB_WR)
		flags |= OCRDMA_CREATE_QP_REQ_INB_WREN_MASK;
	if (qp->cap_flags & OCRDMA_QP_MW_BIND)
		flags |= OCRDMA_CREATE_QP_REQ_BIND_MEMWIN_MASK;
	if (qp->cap_flags & OCRDMA_QP_LKEY0)
		flags |= OCRDMA_CREATE_QP_REQ_ZERO_LKEYEN_MASK;
	if (qp->cap_flags & OCRDMA_QP_FAST_REG)
		flags |= OCRDMA_CREATE_QP_REQ_FMR_EN_MASK;
	return flags;
}