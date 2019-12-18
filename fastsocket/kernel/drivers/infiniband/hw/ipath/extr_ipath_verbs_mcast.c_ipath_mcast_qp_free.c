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
struct ipath_qp {int /*<<< orphan*/  wait; int /*<<< orphan*/  refcount; } ;
struct ipath_mcast_qp {struct ipath_qp* qp; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ipath_mcast_qp*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipath_mcast_qp_free(struct ipath_mcast_qp *mqp)
{
	struct ipath_qp *qp = mqp->qp;

	/* Notify ipath_destroy_qp() if it is waiting. */
	if (atomic_dec_and_test(&qp->refcount))
		wake_up(&qp->wait);

	kfree(mqp);
}