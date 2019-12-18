#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iscsi_task {scalar_t__ state; int /*<<< orphan*/  itt; TYPE_3__* sc; } ;
struct iscsi_conn {TYPE_2__* session; } ;
struct TYPE_6__ {TYPE_1__* device; } ;
struct TYPE_5__ {int cmds_max; struct iscsi_task** cmds; } ;
struct TYPE_4__ {unsigned int lun; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_DBG_SESSION (TYPE_2__*,char*,TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ISCSI_TASK_FREE ; 
 int /*<<< orphan*/  fail_scsi_task (struct iscsi_task*,int) ; 

__attribute__((used)) static void fail_scsi_tasks(struct iscsi_conn *conn, unsigned lun,
			    int error)
{
	struct iscsi_task *task;
	int i;

	for (i = 0; i < conn->session->cmds_max; i++) {
		task = conn->session->cmds[i];
		if (!task->sc || task->state == ISCSI_TASK_FREE)
			continue;

		if (lun != -1 && lun != task->sc->device->lun)
			continue;

		ISCSI_DBG_SESSION(conn->session,
				  "failing sc %p itt 0x%x state %d\n",
				  task->sc, task->itt, task->state);
		fail_scsi_task(task, error);
	}
}