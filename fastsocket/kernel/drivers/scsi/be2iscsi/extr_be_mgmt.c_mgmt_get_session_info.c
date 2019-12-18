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
typedef  int /*<<< orphan*/  u32 ;
struct be_ctrl_info {int /*<<< orphan*/  mbox_lock; } ;
struct beiscsi_hba {struct be_ctrl_info ctrl; } ;
struct be_sge {void* len; void* pa_lo; void* pa_hi; } ;
struct be_mcc_wrb {unsigned int tag0; } ;
struct be_dma_mem {int size; int dma; struct be_cmd_get_session_req* va; } ;
struct be_cmd_get_session_resp {int dummy; } ;
struct be_cmd_get_session_req {int /*<<< orphan*/  session_handle; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int BEISCSI_LOG_CONFIG ; 
 int BEISCSI_LOG_MBOX ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_ISCSI_INI ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  OPCODE_ISCSI_INI_SESSION_GET_A_SESSION ; 
 unsigned int alloc_mcc_tag (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  be_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  be_mcc_notify (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  be_wrb_hdr_prepare (struct be_mcc_wrb*,int,int,int) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int,char*) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (struct be_cmd_get_session_req*,int /*<<< orphan*/ ,int) ; 
 struct be_sge* nonembedded_sgl (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int upper_32_bits (int) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct beiscsi_hba*) ; 

unsigned int mgmt_get_session_info(struct beiscsi_hba *phba,
				   u32 boot_session_handle,
				   struct be_dma_mem *nonemb_cmd)
{
	struct be_ctrl_info *ctrl = &phba->ctrl;
	struct be_mcc_wrb *wrb;
	unsigned int tag = 0;
	struct  be_cmd_get_session_req *req;
	struct be_cmd_get_session_resp *resp;
	struct be_sge *sge;

	beiscsi_log(phba, KERN_INFO,
		    BEISCSI_LOG_CONFIG | BEISCSI_LOG_MBOX,
		    "BG_%d : In beiscsi_get_session_info\n");

	spin_lock(&ctrl->mbox_lock);
	tag = alloc_mcc_tag(phba);
	if (!tag) {
		spin_unlock(&ctrl->mbox_lock);
		return tag;
	}

	nonemb_cmd->size = sizeof(*resp);
	req = nonemb_cmd->va;
	memset(req, 0, sizeof(*req));
	wrb = wrb_from_mccq(phba);
	sge = nonembedded_sgl(wrb);
	wrb->tag0 |= tag;


	wrb->tag0 |= tag;
	be_wrb_hdr_prepare(wrb, sizeof(*req), false, 1);
	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ISCSI_INI,
			   OPCODE_ISCSI_INI_SESSION_GET_A_SESSION,
			   sizeof(*resp));
	req->session_handle = boot_session_handle;
	sge->pa_hi = cpu_to_le32(upper_32_bits(nonemb_cmd->dma));
	sge->pa_lo = cpu_to_le32(nonemb_cmd->dma & 0xFFFFFFFF);
	sge->len = cpu_to_le32(nonemb_cmd->size);

	be_mcc_notify(phba);
	spin_unlock(&ctrl->mbox_lock);
	return tag;
}