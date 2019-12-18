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
struct qib_qp {int /*<<< orphan*/  wait; int /*<<< orphan*/  refcount; } ;
struct qib_mcast_qp {struct qib_qp* qp; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct qib_mcast_qp*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qib_mcast_qp_free(struct qib_mcast_qp *mqp)
{
	struct qib_qp *qp = mqp->qp;

	/* Notify qib_destroy_qp() if it is waiting. */
	if (atomic_dec_and_test(&qp->refcount))
		wake_up(&qp->wait);

	kfree(mqp);
}