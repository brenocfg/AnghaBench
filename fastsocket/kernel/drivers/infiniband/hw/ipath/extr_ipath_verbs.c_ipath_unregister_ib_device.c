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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  table; } ;
struct TYPE_4__ {int /*<<< orphan*/  table; } ;
struct ib_device {int dummy; } ;
struct ipath_ibdev {int /*<<< orphan*/  txreq_bufs; TYPE_1__ lk_table; TYPE_2__ qp_table; int /*<<< orphan*/  dd; int /*<<< orphan*/  rnrwait; int /*<<< orphan*/  piowait; int /*<<< orphan*/ * pending; struct ib_device ibdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_timer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dealloc_device (struct ib_device*) ; 
 int /*<<< orphan*/  ib_unregister_device (struct ib_device*) ; 
 int /*<<< orphan*/  ipath_dev_err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ipath_free_all_qps (TYPE_2__*) ; 
 int /*<<< orphan*/  ipath_mcast_tree_empty () ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void ipath_unregister_ib_device(struct ipath_ibdev *dev)
{
	struct ib_device *ibdev = &dev->ibdev;
	u32 qps_inuse;

	ib_unregister_device(ibdev);

	disable_timer(dev->dd);

	if (!list_empty(&dev->pending[0]) ||
	    !list_empty(&dev->pending[1]) ||
	    !list_empty(&dev->pending[2]))
		ipath_dev_err(dev->dd, "pending list not empty!\n");
	if (!list_empty(&dev->piowait))
		ipath_dev_err(dev->dd, "piowait list not empty!\n");
	if (!list_empty(&dev->rnrwait))
		ipath_dev_err(dev->dd, "rnrwait list not empty!\n");
	if (!ipath_mcast_tree_empty())
		ipath_dev_err(dev->dd, "multicast table memory leak!\n");
	/*
	 * Note that ipath_unregister_ib_device() can be called before all
	 * the QPs are destroyed!
	 */
	qps_inuse = ipath_free_all_qps(&dev->qp_table);
	if (qps_inuse)
		ipath_dev_err(dev->dd, "QP memory leak! %u still in use\n",
			qps_inuse);
	kfree(dev->qp_table.table);
	kfree(dev->lk_table.table);
	kfree(dev->txreq_bufs);
	ib_dealloc_device(ibdev);
}