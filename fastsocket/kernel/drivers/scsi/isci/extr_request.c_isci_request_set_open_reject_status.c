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
struct TYPE_2__ {int open_rej_reason; } ;
struct sas_task {TYPE_1__ task_status; } ;
struct isci_request {int /*<<< orphan*/  flags; } ;
typedef  enum service_response { ____Placeholder_service_response } service_response ;
typedef  enum sas_open_rej_reason { ____Placeholder_sas_open_rej_reason } sas_open_rej_reason ;
typedef  enum exec_status { ____Placeholder_exec_status } exec_status ;

/* Variables and functions */
 int /*<<< orphan*/  IREQ_COMPLETE_IN_TARGET ; 
 int SAS_OPEN_REJECT ; 
 int SAS_TASK_UNDELIVERED ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void isci_request_set_open_reject_status(
	struct isci_request *request,
	struct sas_task *task,
	enum service_response *response_ptr,
	enum exec_status *status_ptr,
	enum sas_open_rej_reason open_rej_reason)
{
	/* Task in the target is done. */
	set_bit(IREQ_COMPLETE_IN_TARGET, &request->flags);
	*response_ptr                     = SAS_TASK_UNDELIVERED;
	*status_ptr                       = SAS_OPEN_REJECT;
	task->task_status.open_rej_reason = open_rej_reason;
}