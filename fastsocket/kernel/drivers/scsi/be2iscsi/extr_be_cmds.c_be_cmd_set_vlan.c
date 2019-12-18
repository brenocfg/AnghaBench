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
typedef  int /*<<< orphan*/  uint16_t ;
struct be_ctrl_info {int /*<<< orphan*/  mbox_lock; } ;
struct beiscsi_hba {int /*<<< orphan*/  interface_handle; struct be_ctrl_info ctrl; } ;
struct be_mcc_wrb {unsigned int tag0; } ;
struct be_cmd_set_vlan_req {int /*<<< orphan*/  vlan_priority; int /*<<< orphan*/  interface_hndl; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUBSYSTEM_ISCSI ; 
 int /*<<< orphan*/  OPCODE_COMMON_ISCSI_NTWK_SET_VLAN ; 
 unsigned int alloc_mcc_tag (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  be_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  be_mcc_notify (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  be_wrb_hdr_prepare (struct be_mcc_wrb*,int,int,int /*<<< orphan*/ ) ; 
 struct be_cmd_set_vlan_req* embedded_payload (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct beiscsi_hba*) ; 

int be_cmd_set_vlan(struct beiscsi_hba *phba,
		     uint16_t vlan_tag)
{
	unsigned int tag = 0;
	struct be_mcc_wrb *wrb;
	struct be_cmd_set_vlan_req *req;
	struct be_ctrl_info *ctrl = &phba->ctrl;

	spin_lock(&ctrl->mbox_lock);
	tag = alloc_mcc_tag(phba);
	if (!tag) {
		spin_unlock(&ctrl->mbox_lock);
		return tag;
	}

	wrb = wrb_from_mccq(phba);
	req = embedded_payload(wrb);
	wrb->tag0 |= tag;
	be_wrb_hdr_prepare(wrb, sizeof(*wrb), true, 0);
	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ISCSI,
			   OPCODE_COMMON_ISCSI_NTWK_SET_VLAN,
			   sizeof(*req));

	req->interface_hndl = phba->interface_handle;
	req->vlan_priority = vlan_tag;

	be_mcc_notify(phba);
	spin_unlock(&ctrl->mbox_lock);

	return tag;
}