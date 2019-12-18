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
struct ipath_ibdev {int /*<<< orphan*/  n_cqs_lock; int /*<<< orphan*/  n_cqs_allocated; } ;
struct ipath_cq {int /*<<< orphan*/  queue; TYPE_1__* ip; int /*<<< orphan*/  comptask; } ;
struct ib_cq {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipath_release_mmap_info ; 
 int /*<<< orphan*/  kfree (struct ipath_cq*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 struct ipath_cq* to_icq (struct ib_cq*) ; 
 struct ipath_ibdev* to_idev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

int ipath_destroy_cq(struct ib_cq *ibcq)
{
	struct ipath_ibdev *dev = to_idev(ibcq->device);
	struct ipath_cq *cq = to_icq(ibcq);

	tasklet_kill(&cq->comptask);
	spin_lock(&dev->n_cqs_lock);
	dev->n_cqs_allocated--;
	spin_unlock(&dev->n_cqs_lock);
	if (cq->ip)
		kref_put(&cq->ip->ref, ipath_release_mmap_info);
	else
		vfree(cq->queue);
	kfree(cq);

	return 0;
}