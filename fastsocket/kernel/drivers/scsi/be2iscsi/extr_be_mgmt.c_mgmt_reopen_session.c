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
struct be_ctrl_info {int /*<<< orphan*/  mbox_lock; } ;
struct beiscsi_hba {struct be_ctrl_info ctrl; } ;
struct be_mcc_wrb {unsigned int tag0; } ;
struct be_cmd_reopen_session_resp {int dummy; } ;
struct be_cmd_reopen_session_req {unsigned int reopen_type; unsigned int session_handle; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int BEISCSI_LOG_CONFIG ; 
 int BEISCSI_LOG_MBOX ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_ISCSI_INI ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  OPCODE_ISCSI_INI_DRIVER_REOPEN_ALL_SESSIONS ; 
 unsigned int alloc_mcc_tag (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  be_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  be_mcc_notify (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  be_wrb_hdr_prepare (struct be_mcc_wrb*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int,char*) ; 
 struct be_cmd_reopen_session_req* embedded_payload (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct beiscsi_hba*) ; 

unsigned int mgmt_reopen_session(struct beiscsi_hba *phba,
				  unsigned int reopen_type,
				  unsigned int sess_handle)
{
	struct be_ctrl_info *ctrl = &phba->ctrl;
	struct be_mcc_wrb *wrb;
	struct be_cmd_reopen_session_req *req;
	unsigned int tag = 0;

	beiscsi_log(phba, KERN_INFO,
		    BEISCSI_LOG_CONFIG | BEISCSI_LOG_MBOX,
		    "BG_%d : In bescsi_get_boot_target\n");

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
	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ISCSI_INI,
			   OPCODE_ISCSI_INI_DRIVER_REOPEN_ALL_SESSIONS,
			   sizeof(struct be_cmd_reopen_session_resp));

	/* set the reopen_type,sess_handle */
	req->reopen_type = reopen_type;
	req->session_handle = sess_handle;

	be_mcc_notify(phba);
	spin_unlock(&ctrl->mbox_lock);
	return tag;
}