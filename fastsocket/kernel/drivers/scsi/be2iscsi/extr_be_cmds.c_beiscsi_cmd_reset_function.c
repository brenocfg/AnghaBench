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
struct be_ctrl_info {int /*<<< orphan*/  mbox_lock; int /*<<< orphan*/  mbox_mem; } ;
struct beiscsi_hba {struct be_ctrl_info ctrl; } ;
struct be_post_sgl_pages_req {int /*<<< orphan*/  hdr; } ;
struct be_mcc_wrb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int /*<<< orphan*/  OPCODE_COMMON_FUNCTION_RESET ; 
 int /*<<< orphan*/  be_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int be_mbox_notify_wait (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  be_wrb_hdr_prepare (struct be_mcc_wrb*,int,int,int /*<<< orphan*/ ) ; 
 struct be_post_sgl_pages_req* embedded_payload (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mbox (int /*<<< orphan*/ *) ; 

int beiscsi_cmd_reset_function(struct beiscsi_hba  *phba)
{
	struct be_ctrl_info *ctrl = &phba->ctrl;
	struct be_mcc_wrb *wrb = wrb_from_mbox(&ctrl->mbox_mem);
	struct be_post_sgl_pages_req *req = embedded_payload(wrb);
	int status;

	spin_lock(&ctrl->mbox_lock);

	req = embedded_payload(wrb);
	be_wrb_hdr_prepare(wrb, sizeof(*req), true, 0);
	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			   OPCODE_COMMON_FUNCTION_RESET, sizeof(*req));
	status = be_mbox_notify_wait(phba);

	spin_unlock(&ctrl->mbox_lock);
	return status;
}