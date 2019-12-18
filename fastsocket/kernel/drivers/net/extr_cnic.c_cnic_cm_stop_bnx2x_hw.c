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
struct cnic_local {int /*<<< orphan*/  iscsi_conn; int /*<<< orphan*/  delete_task; int /*<<< orphan*/  ctx_tbl; } ;
struct cnic_dev {int /*<<< orphan*/  netdev; struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cnic_bnx2x_delete_wait (struct cnic_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnic_wq ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cnic_cm_stop_bnx2x_hw(struct cnic_dev *dev)
{
	struct cnic_local *cp = dev->cnic_priv;

	if (!cp->ctx_tbl)
		return;

	if (!netif_running(dev->netdev))
		return;

	cnic_bnx2x_delete_wait(dev, 0);

	cancel_delayed_work(&cp->delete_task);
	flush_workqueue(cnic_wq);

	if (atomic_read(&cp->iscsi_conn) != 0)
		netdev_warn(dev->netdev, "%d iSCSI connections not destroyed\n",
			    atomic_read(&cp->iscsi_conn));
}