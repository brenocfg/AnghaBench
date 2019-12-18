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
struct TYPE_4__ {unsigned short* vendor_cmd; } ;
struct TYPE_5__ {TYPE_1__ h_vendor; } ;
struct iscsi_bsg_request {TYPE_2__ rqst_data; } ;
struct TYPE_6__ {int payload_len; int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg_list; } ;
struct bsg_job {TYPE_3__ request_payload; int /*<<< orphan*/  request_len; struct iscsi_bsg_request* request; } ;
struct beiscsi_hba {int dummy; } ;
struct be_sge {void* len; void* pa_lo; void* pa_hi; } ;
struct be_mcc_wrb {unsigned short region; unsigned short sector; unsigned short offset; unsigned int tag0; int /*<<< orphan*/  hdr; } ;
struct be_dma_mem {int size; int dma; struct be_mcc_wrb* va; } ;
struct be_ctrl_info {int /*<<< orphan*/  mbox_lock; } ;
struct be_cmd_resp_hdr {unsigned short region; unsigned short sector; unsigned short offset; unsigned int tag0; int /*<<< orphan*/  hdr; } ;
struct be_bsg_vendor_cmd {unsigned short region; unsigned short sector; unsigned short offset; unsigned int tag0; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
#define  BEISCSI_READ_FLASH 129 
#define  BEISCSI_WRITE_FLASH 128 
 int /*<<< orphan*/  CMD_SUBSYSTEM_ISCSI ; 
 unsigned int ENOSYS ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  OPCODE_COMMON_READ_FLASH ; 
 int /*<<< orphan*/  OPCODE_COMMON_WRITE_FLASH ; 
 unsigned int alloc_mcc_tag (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  be_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  be_mcc_notify (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  be_wrb_hdr_prepare (struct be_mcc_wrb*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,short) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (struct be_mcc_wrb*,int /*<<< orphan*/ ,int) ; 
 struct be_sge* nonembedded_sgl (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct be_mcc_wrb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int upper_32_bits (int) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct beiscsi_hba*) ; 

unsigned int mgmt_vendor_specific_fw_cmd(struct be_ctrl_info *ctrl,
					 struct beiscsi_hba *phba,
					 struct bsg_job *job,
					 struct be_dma_mem *nonemb_cmd)
{
	struct be_cmd_resp_hdr *resp;
	struct be_mcc_wrb *wrb = wrb_from_mccq(phba);
	struct be_sge *mcc_sge = nonembedded_sgl(wrb);
	unsigned int tag = 0;
	struct iscsi_bsg_request *bsg_req = job->request;
	struct be_bsg_vendor_cmd *req = nonemb_cmd->va;
	unsigned short region, sector_size, sector, offset;

	nonemb_cmd->size = job->request_payload.payload_len;
	memset(nonemb_cmd->va, 0, nonemb_cmd->size);
	resp = nonemb_cmd->va;
	region =  bsg_req->rqst_data.h_vendor.vendor_cmd[1];
	sector_size =  bsg_req->rqst_data.h_vendor.vendor_cmd[2];
	sector =  bsg_req->rqst_data.h_vendor.vendor_cmd[3];
	offset =  bsg_req->rqst_data.h_vendor.vendor_cmd[4];
	req->region = region;
	req->sector = sector;
	req->offset = offset;
	spin_lock(&ctrl->mbox_lock);
	memset(wrb, 0, sizeof(*wrb));

	switch (bsg_req->rqst_data.h_vendor.vendor_cmd[0]) {
	case BEISCSI_WRITE_FLASH:
		offset = sector * sector_size + offset;
		be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ISCSI,
				   OPCODE_COMMON_WRITE_FLASH, sizeof(*req));
		sg_copy_to_buffer(job->request_payload.sg_list,
				  job->request_payload.sg_cnt,
				  nonemb_cmd->va + offset, job->request_len);
		break;
	case BEISCSI_READ_FLASH:
		be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ISCSI,
			   OPCODE_COMMON_READ_FLASH, sizeof(*req));
		break;
	default:
		beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_CONFIG,
			    "BG_%d : Unsupported cmd = 0x%x\n\n",
			    bsg_req->rqst_data.h_vendor.vendor_cmd[0]);

		spin_unlock(&ctrl->mbox_lock);
		return -ENOSYS;
	}

	tag = alloc_mcc_tag(phba);
	if (!tag) {
		spin_unlock(&ctrl->mbox_lock);
		return tag;
	}

	be_wrb_hdr_prepare(wrb, nonemb_cmd->size, false,
			   job->request_payload.sg_cnt);
	mcc_sge->pa_hi = cpu_to_le32(upper_32_bits(nonemb_cmd->dma));
	mcc_sge->pa_lo = cpu_to_le32(nonemb_cmd->dma & 0xFFFFFFFF);
	mcc_sge->len = cpu_to_le32(nonemb_cmd->size);
	wrb->tag0 |= tag;

	be_mcc_notify(phba);

	spin_unlock(&ctrl->mbox_lock);
	return tag;
}