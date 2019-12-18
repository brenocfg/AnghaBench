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
struct iscsi_task {int /*<<< orphan*/  last_xfer; } ;
struct iscsi_conn {struct iscsi_task* task; TYPE_2__* session; int /*<<< orphan*/  suspend_tx; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_1__* tt; } ;
struct TYPE_3__ {int (* xmit_task ) (struct iscsi_task*) ;} ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  ISCSI_SUSPEND_BIT ; 
 int /*<<< orphan*/  __iscsi_get_task (struct iscsi_task*) ; 
 int /*<<< orphan*/  __iscsi_put_task (struct iscsi_task*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (struct iscsi_task*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iscsi_xmit_task(struct iscsi_conn *conn)
{
	struct iscsi_task *task = conn->task;
	int rc;

	if (test_bit(ISCSI_SUSPEND_BIT, &conn->suspend_tx))
		return -ENODATA;

	__iscsi_get_task(task);
	spin_unlock_bh(&conn->session->lock);
	rc = conn->session->tt->xmit_task(task);
	spin_lock_bh(&conn->session->lock);
	if (!rc) {
		/* done with this task */
		task->last_xfer = jiffies;
		conn->task = NULL;
	}
	__iscsi_put_task(task);
	return rc;
}