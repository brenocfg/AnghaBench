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
typedef  int /*<<< orphan*/  u32 ;
struct sas_task {scalar_t__ data_dir; } ;
struct TYPE_3__ {int status; } ;
struct TYPE_4__ {TYPE_1__ rsp; } ;
struct isci_request {int sci_status; int /*<<< orphan*/  sm; int /*<<< orphan*/  scu_status; TYPE_2__ stp; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;

/* Variables and functions */
 int ATA_ERR ; 
 scalar_t__ DMA_NONE ; 
 int SCI_IO_FAILURE_RESPONSE_VALID ; 
 int /*<<< orphan*/  SCI_REQ_COMPLETED ; 
 int SCI_SUCCESS ; 
 int /*<<< orphan*/  SCU_TASK_DONE_CHECK_RESPONSE ; 
 int /*<<< orphan*/  SCU_TASK_DONE_GOOD ; 
 struct sas_task* isci_request_access_task (struct isci_request*) ; 
 int process_unsolicited_fis (struct isci_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum sci_status atapi_d2h_reg_frame_handler(struct isci_request *ireq,
						   u32 frame_index)
{
	struct sas_task *task = isci_request_access_task(ireq);
	enum sci_status status;

	status = process_unsolicited_fis(ireq, frame_index);

	if (status == SCI_SUCCESS) {
		if (ireq->stp.rsp.status & ATA_ERR)
			status = SCI_IO_FAILURE_RESPONSE_VALID;
	} else {
		status = SCI_IO_FAILURE_RESPONSE_VALID;
	}

	if (status != SCI_SUCCESS) {
		ireq->scu_status = SCU_TASK_DONE_CHECK_RESPONSE;
		ireq->sci_status = status;
	} else {
		ireq->scu_status = SCU_TASK_DONE_GOOD;
		ireq->sci_status = SCI_SUCCESS;
	}

	/* the d2h ufi is the end of non-data commands */
	if (task->data_dir == DMA_NONE)
		sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);

	return status;
}