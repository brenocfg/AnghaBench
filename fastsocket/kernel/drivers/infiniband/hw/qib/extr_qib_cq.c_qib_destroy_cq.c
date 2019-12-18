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
struct qib_ibdev {int /*<<< orphan*/  n_cqs_lock; int /*<<< orphan*/  n_cqs_allocated; } ;
struct qib_cq {int /*<<< orphan*/  queue; TYPE_1__* ip; int /*<<< orphan*/  comptask; } ;
struct ib_cq {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct qib_cq*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_release_mmap_info ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct qib_cq* to_icq (struct ib_cq*) ; 
 struct qib_ibdev* to_idev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

int qib_destroy_cq(struct ib_cq *ibcq)
{
	struct qib_ibdev *dev = to_idev(ibcq->device);
	struct qib_cq *cq = to_icq(ibcq);

	flush_work(&cq->comptask);
	spin_lock(&dev->n_cqs_lock);
	dev->n_cqs_allocated--;
	spin_unlock(&dev->n_cqs_lock);
	if (cq->ip)
		kref_put(&cq->ip->ref, qib_release_mmap_info);
	else
		vfree(cq->queue);
	kfree(cq);

	return 0;
}