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
struct ssp_task_iu {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  frame_type; } ;
struct TYPE_3__ {TYPE_2__ ssp; } ;
struct scu_task_context {int control_frame; int ssp_command_iu_length; TYPE_1__ type; scalar_t__ transfer_length_bytes; int /*<<< orphan*/  task_type; int /*<<< orphan*/  priority; } ;
struct isci_request {struct scu_task_context* tc; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCU_TASK_PRIORITY_HIGH ; 
 int /*<<< orphan*/  SCU_TASK_TYPE_RAW_FRAME ; 
 int /*<<< orphan*/  SSP_TASK ; 
 int /*<<< orphan*/  scu_ssp_reqeust_construct_task_context (struct isci_request*,struct scu_task_context*) ; 

__attribute__((used)) static void scu_ssp_task_request_construct_task_context(struct isci_request *ireq)
{
	struct scu_task_context *task_context = ireq->tc;

	scu_ssp_reqeust_construct_task_context(ireq, task_context);

	task_context->control_frame                = 1;
	task_context->priority                     = SCU_TASK_PRIORITY_HIGH;
	task_context->task_type                    = SCU_TASK_TYPE_RAW_FRAME;
	task_context->transfer_length_bytes        = 0;
	task_context->type.ssp.frame_type          = SSP_TASK;
	task_context->ssp_command_iu_length =
		sizeof(struct ssp_task_iu) / sizeof(u32);
}