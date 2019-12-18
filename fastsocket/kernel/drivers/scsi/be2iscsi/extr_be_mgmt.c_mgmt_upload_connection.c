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
struct tcp_upload_params_in {unsigned short id; unsigned char upload_type; int /*<<< orphan*/  hdr; } ;
struct be_ctrl_info {int /*<<< orphan*/  mbox_lock; } ;
struct beiscsi_hba {struct be_ctrl_info ctrl; } ;
struct be_mcc_wrb {unsigned int tag0; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_COMMON_TCP_UPLOAD ; 
 int /*<<< orphan*/  OPCODE_COMMON_TCP_UPLOAD ; 
 unsigned int alloc_mcc_tag (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  be_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  be_mcc_notify (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  be_wrb_hdr_prepare (struct be_mcc_wrb*,int,int,int /*<<< orphan*/ ) ; 
 struct tcp_upload_params_in* embedded_payload (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct beiscsi_hba*) ; 

unsigned int mgmt_upload_connection(struct beiscsi_hba *phba,
				unsigned short cid, unsigned int upload_flag)
{
	struct be_ctrl_info *ctrl = &phba->ctrl;
	struct be_mcc_wrb *wrb;
	struct tcp_upload_params_in *req;
	unsigned int tag = 0;

	spin_lock(&ctrl->mbox_lock);
	tag = alloc_mcc_tag(phba);
	if (!tag) {
		spin_unlock(&ctrl->mbox_lock);
		return tag;
	}
	wrb = wrb_from_mccq(phba);
	req = embedded_payload(wrb);
	wrb->tag0 |= tag;

	be_wrb_hdr_prepare(wrb, sizeof(*req), true, 0);
	be_cmd_hdr_prepare(&req->hdr, CMD_COMMON_TCP_UPLOAD,
			   OPCODE_COMMON_TCP_UPLOAD, sizeof(*req));
	req->id = (unsigned short)cid;
	req->upload_type = (unsigned char)upload_flag;
	be_mcc_notify(phba);
	spin_unlock(&ctrl->mbox_lock);
	return tag;
}