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
struct scsi_cmnd {TYPE_1__* device; } ;
struct sas_task {int dummy; } ;
struct sas_internal {TYPE_2__* dft; } ;
struct Scsi_Host {scalar_t__ ehandler; int /*<<< orphan*/  transportt; } ;
struct TYPE_4__ {int (* lldd_abort_task ) (struct sas_task*) ;} ;
struct TYPE_3__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int FAILED ; 
 int SUCCESS ; 
 int TMF_RESP_FUNC_COMPLETE ; 
 int TMF_RESP_FUNC_SUCC ; 
 struct sas_task* TO_SAS_TASK (struct scsi_cmnd*) ; 
 scalar_t__ current ; 
 int stub1 (struct sas_task*) ; 
 struct sas_internal* to_sas_internal (int /*<<< orphan*/ ) ; 

int sas_eh_abort_handler(struct scsi_cmnd *cmd)
{
	int res;
	struct sas_task *task = TO_SAS_TASK(cmd);
	struct Scsi_Host *host = cmd->device->host;
	struct sas_internal *i = to_sas_internal(host->transportt);

	if (current != host->ehandler)
		return FAILED;

	if (!i->dft->lldd_abort_task)
		return FAILED;

	res = i->dft->lldd_abort_task(task);
	if (res == TMF_RESP_FUNC_SUCC || res == TMF_RESP_FUNC_COMPLETE)
		return SUCCESS;

	return FAILED;
}