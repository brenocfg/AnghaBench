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
struct TYPE_4__ {int /*<<< orphan*/  iscsi_features; } ;
struct beiscsi_hba {int /*<<< orphan*/  fw_ver_str; TYPE_1__ fw_config; } ;
struct be_sge {void* len; void* pa_lo; void* pa_hi; } ;
struct TYPE_5__ {int /*<<< orphan*/  firmware_version_string; int /*<<< orphan*/  iscsi_features; int /*<<< orphan*/  flashrom_version_string; } ;
struct TYPE_6__ {TYPE_2__ hba_attribs; } ;
struct be_mgmt_controller_attributes_resp {TYPE_3__ params; int /*<<< orphan*/  hdr; } ;
struct be_mgmt_controller_attributes {TYPE_3__ params; int /*<<< orphan*/  hdr; } ;
struct be_mcc_wrb {TYPE_3__ params; int /*<<< orphan*/  hdr; } ;
struct be_dma_mem {int dma; int size; struct be_mgmt_controller_attributes_resp* va; } ;
struct be_ctrl_info {int /*<<< orphan*/  pdev; int /*<<< orphan*/  mbox_lock; int /*<<< orphan*/  mbox_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_INIT ; 
 int /*<<< orphan*/  BEISCSI_VER_STRLEN ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  OPCODE_COMMON_GET_CNTL_ATTRIBUTES ; 
 int /*<<< orphan*/  be_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int be_mbox_notify (struct be_ctrl_info*) ; 
 int /*<<< orphan*/  be_wrb_hdr_prepare (struct be_mgmt_controller_attributes_resp*,int,int,int) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct be_mgmt_controller_attributes_resp*,int /*<<< orphan*/ ,int) ; 
 struct be_sge* nonembedded_sgl (struct be_mgmt_controller_attributes_resp*) ; 
 struct be_mgmt_controller_attributes_resp* pci_alloc_consistent (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,struct be_mgmt_controller_attributes_resp*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int upper_32_bits (int) ; 
 struct be_mgmt_controller_attributes_resp* wrb_from_mbox (int /*<<< orphan*/ *) ; 

int mgmt_check_supported_fw(struct be_ctrl_info *ctrl,
				      struct beiscsi_hba *phba)
{
	struct be_dma_mem nonemb_cmd;
	struct be_mcc_wrb *wrb = wrb_from_mbox(&ctrl->mbox_mem);
	struct be_mgmt_controller_attributes *req;
	struct be_sge *sge = nonembedded_sgl(wrb);
	int status = 0;

	nonemb_cmd.va = pci_alloc_consistent(ctrl->pdev,
				sizeof(struct be_mgmt_controller_attributes),
				&nonemb_cmd.dma);
	if (nonemb_cmd.va == NULL) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BG_%d : Failed to allocate memory for "
			    "mgmt_check_supported_fw\n");
		return -ENOMEM;
	}
	nonemb_cmd.size = sizeof(struct be_mgmt_controller_attributes);
	req = nonemb_cmd.va;
	memset(req, 0, sizeof(*req));
	spin_lock(&ctrl->mbox_lock);
	memset(wrb, 0, sizeof(*wrb));
	be_wrb_hdr_prepare(wrb, sizeof(*req), false, 1);
	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			   OPCODE_COMMON_GET_CNTL_ATTRIBUTES, sizeof(*req));
	sge->pa_hi = cpu_to_le32(upper_32_bits(nonemb_cmd.dma));
	sge->pa_lo = cpu_to_le32(nonemb_cmd.dma & 0xFFFFFFFF);
	sge->len = cpu_to_le32(nonemb_cmd.size);
	status = be_mbox_notify(ctrl);
	if (!status) {
		struct be_mgmt_controller_attributes_resp *resp = nonemb_cmd.va;
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
			    "BG_%d : Firmware Version of CMD : %s\n"
			    "Firmware Version is : %s\n"
			    "Developer Build, not performing version check...\n",
			    resp->params.hba_attribs
			    .flashrom_version_string,
			    resp->params.hba_attribs.
			    firmware_version_string);

		phba->fw_config.iscsi_features =
				resp->params.hba_attribs.iscsi_features;
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
			    "BM_%d : phba->fw_config.iscsi_features = %d\n",
			    phba->fw_config.iscsi_features);
		memcpy(phba->fw_ver_str, resp->params.hba_attribs.
		       firmware_version_string, BEISCSI_VER_STRLEN);
	} else
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BG_%d :  Failed in mgmt_check_supported_fw\n");
	spin_unlock(&ctrl->mbox_lock);
	if (nonemb_cmd.va)
		pci_free_consistent(ctrl->pdev, nonemb_cmd.size,
				    nonemb_cmd.va, nonemb_cmd.dma);

	return status;
}