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
struct scsi_lun {int /*<<< orphan*/  scsi_lun; } ;
struct scsi_cmnd {int /*<<< orphan*/  sc_data_direction; int /*<<< orphan*/ * cmnd; TYPE_1__* device; } ;
struct TYPE_4__ {int retry_count; int /*<<< orphan*/  cdb; int /*<<< orphan*/  task_attr; int /*<<< orphan*/  LUN; } ;
struct sas_task {int /*<<< orphan*/  task_done; int /*<<< orphan*/  data_dir; int /*<<< orphan*/  total_xfer_len; int /*<<< orphan*/  num_scatter; int /*<<< orphan*/  scatter; TYPE_2__ ssp_task; struct domain_device* dev; int /*<<< orphan*/  task_proto; struct scsi_cmnd* uldd_task; } ;
struct domain_device {int /*<<< orphan*/  tproto; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_3__ {int /*<<< orphan*/  lun; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSIGN_SAS_TASK (struct scsi_cmnd*,struct sas_task*) ; 
 int /*<<< orphan*/  TASK_ATTR_SIMPLE ; 
 int /*<<< orphan*/  int_to_scsilun (int /*<<< orphan*/ ,struct scsi_lun*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct sas_task* sas_alloc_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_scsi_task_done ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 

__attribute__((used)) static struct sas_task *sas_create_task(struct scsi_cmnd *cmd,
					       struct domain_device *dev,
					       gfp_t gfp_flags)
{
	struct sas_task *task = sas_alloc_task(gfp_flags);
	struct scsi_lun lun;

	if (!task)
		return NULL;

	task->uldd_task = cmd;
	ASSIGN_SAS_TASK(cmd, task);

	task->dev = dev;
	task->task_proto = task->dev->tproto; /* BUG_ON(!SSP) */

	task->ssp_task.retry_count = 1;
	int_to_scsilun(cmd->device->lun, &lun);
	memcpy(task->ssp_task.LUN, &lun.scsi_lun, 8);
	task->ssp_task.task_attr = TASK_ATTR_SIMPLE;
	memcpy(task->ssp_task.cdb, cmd->cmnd, 16);

	task->scatter = scsi_sglist(cmd);
	task->num_scatter = scsi_sg_count(cmd);
	task->total_xfer_len = scsi_bufflen(cmd);
	task->data_dir = cmd->sc_data_direction;

	task->task_done = sas_scsi_task_done;

	return task;
}