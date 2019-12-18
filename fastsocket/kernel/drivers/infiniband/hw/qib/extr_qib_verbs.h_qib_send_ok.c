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
struct qib_qp {int s_flags; scalar_t__ s_hdrwords; } ;

/* Variables and functions */
 int QIB_S_ANY_WAIT_IO ; 
 int QIB_S_ANY_WAIT_SEND ; 
 int QIB_S_BUSY ; 
 int QIB_S_RESP_PENDING ; 

__attribute__((used)) static inline int qib_send_ok(struct qib_qp *qp)
{
	return !(qp->s_flags & (QIB_S_BUSY | QIB_S_ANY_WAIT_IO)) &&
		(qp->s_hdrwords || (qp->s_flags & QIB_S_RESP_PENDING) ||
		 !(qp->s_flags & QIB_S_ANY_WAIT_SEND));
}