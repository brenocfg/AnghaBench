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
struct iscsi_task {int state; int /*<<< orphan*/  running; int /*<<< orphan*/  sc; int /*<<< orphan*/  itt; struct iscsi_conn* conn; } ;
struct iscsi_conn {struct iscsi_task* ping_task; struct iscsi_task* task; int /*<<< orphan*/  session; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_DBG_SESSION (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ISCSI_TASK_ABRT_SESS_RECOV ; 
 int ISCSI_TASK_ABRT_TMF ; 
 int ISCSI_TASK_COMPLETED ; 
 int ISCSI_TASK_FREE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __iscsi_put_task (struct iscsi_task*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iscsi_complete_task(struct iscsi_task *task, int state)
{
	struct iscsi_conn *conn = task->conn;

	ISCSI_DBG_SESSION(conn->session,
			  "complete task itt 0x%x state %d sc %p\n",
			  task->itt, task->state, task->sc);
	if (task->state == ISCSI_TASK_COMPLETED ||
	    task->state == ISCSI_TASK_ABRT_TMF ||
	    task->state == ISCSI_TASK_ABRT_SESS_RECOV)
		return;
	WARN_ON_ONCE(task->state == ISCSI_TASK_FREE);
	task->state = state;

	if (!list_empty(&task->running))
		list_del_init(&task->running);

	if (conn->task == task)
		conn->task = NULL;

	if (conn->ping_task == task)
		conn->ping_task = NULL;

	/* release get from queueing */
	__iscsi_put_task(task);
}