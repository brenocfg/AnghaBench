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
typedef  size_t u32 ;
struct ipath_qp {size_t s_lsn; int s_flags; scalar_t__ s_cur; scalar_t__ s_head; } ;
struct TYPE_2__ {size_t ssn; } ;

/* Variables and functions */
 size_t IPATH_AETH_CREDIT_INVAL ; 
 size_t IPATH_AETH_CREDIT_MASK ; 
 size_t IPATH_AETH_CREDIT_SHIFT ; 
 size_t IPATH_MSN_MASK ; 
 int IPATH_S_WAIT_SSN_CREDIT ; 
 size_t* credit_table ; 
 TYPE_1__* get_swqe_ptr (struct ipath_qp*,scalar_t__) ; 
 scalar_t__ ipath_cmp24 (size_t,size_t) ; 
 int /*<<< orphan*/  ipath_schedule_send (struct ipath_qp*) ; 

void ipath_get_credit(struct ipath_qp *qp, u32 aeth)
{
	u32 credit = (aeth >> IPATH_AETH_CREDIT_SHIFT) & IPATH_AETH_CREDIT_MASK;

	/*
	 * If the credit is invalid, we can send
	 * as many packets as we like.  Otherwise, we have to
	 * honor the credit field.
	 */
	if (credit == IPATH_AETH_CREDIT_INVAL)
		qp->s_lsn = (u32) -1;
	else if (qp->s_lsn != (u32) -1) {
		/* Compute new LSN (i.e., MSN + credit) */
		credit = (aeth + credit_table[credit]) & IPATH_MSN_MASK;
		if (ipath_cmp24(credit, qp->s_lsn) > 0)
			qp->s_lsn = credit;
	}

	/* Restart sending if it was blocked due to lack of credits. */
	if ((qp->s_flags & IPATH_S_WAIT_SSN_CREDIT) &&
	    qp->s_cur != qp->s_head &&
	    (qp->s_lsn == (u32) -1 ||
	     ipath_cmp24(get_swqe_ptr(qp, qp->s_cur)->ssn,
			 qp->s_lsn + 1) <= 0))
		ipath_schedule_send(qp);
}