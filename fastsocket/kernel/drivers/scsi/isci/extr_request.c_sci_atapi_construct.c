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
struct sas_task {scalar_t__ data_dir; scalar_t__ total_xfer_len; } ;
struct TYPE_3__ {scalar_t__ fis_type; } ;
struct host_to_dev_fis {int /*<<< orphan*/  features; } ;
struct TYPE_4__ {TYPE_1__ rsp; struct host_to_dev_fis cmd; } ;
struct isci_request {TYPE_2__ stp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATAPI_PKT_DMA ; 
 scalar_t__ DMA_NONE ; 
 struct sas_task* isci_request_access_task (struct isci_request*) ; 
 int /*<<< orphan*/  scu_stp_raw_request_construct_task_context (struct isci_request*) ; 

__attribute__((used)) static void sci_atapi_construct(struct isci_request *ireq)
{
	struct host_to_dev_fis *h2d_fis = &ireq->stp.cmd;
	struct sas_task *task;

	/* To simplify the implementation we take advantage of the
	 * silicon's partial acceleration of atapi protocol (dma data
	 * transfers), so we promote all commands to dma protocol.  This
	 * breaks compatibility with ATA_HORKAGE_ATAPI_MOD16_DMA drives.
	 */
	h2d_fis->features |= ATAPI_PKT_DMA;

	scu_stp_raw_request_construct_task_context(ireq);

	task = isci_request_access_task(ireq);
	if (task->data_dir == DMA_NONE)
		task->total_xfer_len = 0;

	/* clear the response so we can detect arrivial of an
	 * unsolicited h2d fis
	 */
	ireq->stp.rsp.fis_type = 0;
}