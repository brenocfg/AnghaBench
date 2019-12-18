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
typedef  int u64 ;
typedef  int u32 ;
struct hptiop_hba {int msg_done; TYPE_2__* reqs; } ;
struct TYPE_3__ {int /*<<< orphan*/  result; } ;
struct hpt_iop_request_scsi_command {TYPE_1__ header; } ;
struct TYPE_4__ {struct hpt_iop_request_scsi_command* req_virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  IOP_REQUEST_TYPE_GET_CONFIG 130 
#define  IOP_REQUEST_TYPE_SCSI_COMMAND 129 
#define  IOP_REQUEST_TYPE_SET_CONFIG 128 
 int /*<<< orphan*/  IOP_RESULT_SUCCESS ; 
 int MVIOP_MU_QUEUE_REQUEST_RESULT_BIT ; 
 int MVIOP_MU_QUEUE_REQUEST_RETURN_CONTEXT ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/  hptiop_finish_scsi_req (struct hptiop_hba*,int,struct hpt_iop_request_scsi_command*) ; 
 int /*<<< orphan*/  likely (int) ; 

__attribute__((used)) static void hptiop_request_callback_mv(struct hptiop_hba *hba, u64 tag)
{
	u32 req_type = (tag >> 5) & 0x7;
	struct hpt_iop_request_scsi_command *req;

	dprintk("hptiop_request_callback_mv: tag=%llx\n", tag);

	BUG_ON((tag & MVIOP_MU_QUEUE_REQUEST_RETURN_CONTEXT) == 0);

	switch (req_type) {
	case IOP_REQUEST_TYPE_GET_CONFIG:
	case IOP_REQUEST_TYPE_SET_CONFIG:
		hba->msg_done = 1;
		break;

	case IOP_REQUEST_TYPE_SCSI_COMMAND:
		req = hba->reqs[tag >> 8].req_virt;
		if (likely(tag & MVIOP_MU_QUEUE_REQUEST_RESULT_BIT))
			req->header.result = cpu_to_le32(IOP_RESULT_SUCCESS);

		hptiop_finish_scsi_req(hba, tag>>8, req);
		break;

	default:
		break;
	}
}