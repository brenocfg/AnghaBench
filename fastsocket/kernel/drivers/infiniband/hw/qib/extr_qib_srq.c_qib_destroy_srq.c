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
struct TYPE_3__ {int /*<<< orphan*/  wq; } ;
struct qib_srq {TYPE_1__ rq; TYPE_2__* ip; } ;
struct qib_ibdev {int /*<<< orphan*/  n_srqs_lock; int /*<<< orphan*/  n_srqs_allocated; } ;
struct ib_srq {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct qib_srq*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_release_mmap_info ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct qib_ibdev* to_idev (int /*<<< orphan*/ ) ; 
 struct qib_srq* to_isrq (struct ib_srq*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

int qib_destroy_srq(struct ib_srq *ibsrq)
{
	struct qib_srq *srq = to_isrq(ibsrq);
	struct qib_ibdev *dev = to_idev(ibsrq->device);

	spin_lock(&dev->n_srqs_lock);
	dev->n_srqs_allocated--;
	spin_unlock(&dev->n_srqs_lock);
	if (srq->ip)
		kref_put(&srq->ip->ref, qib_release_mmap_info);
	else
		vfree(srq->rq.wq);
	kfree(srq);

	return 0;
}