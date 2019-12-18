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
struct qib_qp {int /*<<< orphan*/  refcount; } ;
struct qib_mcast_qp {struct qib_qp* qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct qib_mcast_qp* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct qib_mcast_qp *qib_mcast_qp_alloc(struct qib_qp *qp)
{
	struct qib_mcast_qp *mqp;

	mqp = kmalloc(sizeof *mqp, GFP_KERNEL);
	if (!mqp)
		goto bail;

	mqp->qp = qp;
	atomic_inc(&qp->refcount);

bail:
	return mqp;
}