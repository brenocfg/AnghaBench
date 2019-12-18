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
struct iscsi_task {int /*<<< orphan*/  running; struct iscsi_conn* conn; } ;
struct iscsi_conn {int /*<<< orphan*/  requeue; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsi_conn_queue_work (struct iscsi_conn*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

void iscsi_requeue_task(struct iscsi_task *task)
{
	struct iscsi_conn *conn = task->conn;

	/*
	 * this may be on the requeue list already if the xmit_task callout
	 * is handling the r2ts while we are adding new ones
	 */
	if (list_empty(&task->running))
		list_add_tail(&task->running, &conn->requeue);
	iscsi_conn_queue_work(conn);
}