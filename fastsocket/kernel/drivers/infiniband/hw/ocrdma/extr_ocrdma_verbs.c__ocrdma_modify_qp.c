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
struct ocrdma_qp {struct ocrdma_dev* dev; } ;
struct ocrdma_dev {int dummy; } ;
struct ib_qp_attr {int /*<<< orphan*/  qp_state; } ;
struct ib_qp {int dummy; } ;
typedef  enum ib_qp_state { ____Placeholder_ib_qp_state } ib_qp_state ;

/* Variables and functions */
 int IB_QP_STATE ; 
 struct ocrdma_qp* get_ocrdma_qp (struct ib_qp*) ; 
 int ocrdma_mbx_modify_qp (struct ocrdma_dev*,struct ocrdma_qp*,struct ib_qp_attr*,int,int) ; 
 int ocrdma_qp_state_machine (struct ocrdma_qp*,int /*<<< orphan*/ ,int*) ; 

int _ocrdma_modify_qp(struct ib_qp *ibqp, struct ib_qp_attr *attr,
		      int attr_mask)
{
	int status = 0;
	struct ocrdma_qp *qp;
	struct ocrdma_dev *dev;
	enum ib_qp_state old_qps;

	qp = get_ocrdma_qp(ibqp);
	dev = qp->dev;
	if (attr_mask & IB_QP_STATE)
		status = ocrdma_qp_state_machine(qp, attr->qp_state, &old_qps);
	/* if new and previous states are same hw doesn't need to
	 * know about it.
	 */
	if (status < 0)
		return status;
	status = ocrdma_mbx_modify_qp(dev, qp, attr, attr_mask, old_qps);
	return status;
}