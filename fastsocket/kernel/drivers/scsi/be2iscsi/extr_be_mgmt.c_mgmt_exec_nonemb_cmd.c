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
struct be_ctrl_info {int /*<<< orphan*/  pdev; int /*<<< orphan*/  mbox_lock; } ;
struct beiscsi_hba {struct be_ctrl_info ctrl; } ;
struct be_sge {void* len; void* pa_lo; void* pa_hi; } ;
struct be_mcc_wrb {unsigned int tag0; } ;
struct be_dma_mem {int /*<<< orphan*/  dma; int /*<<< orphan*/  va; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int BEISCSI_LOG_CONFIG ; 
 int BEISCSI_LOG_MBOX ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KERN_ERR ; 
 unsigned int alloc_mcc_tag (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  be_mcc_notify (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  be_wrb_hdr_prepare (struct be_mcc_wrb*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int,char*) ; 
 int beiscsi_mccq_compl (struct beiscsi_hba*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct be_mcc_wrb*,int /*<<< orphan*/ ,int) ; 
 struct be_sge* nonembedded_sgl (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct beiscsi_hba*) ; 

__attribute__((used)) static int mgmt_exec_nonemb_cmd(struct beiscsi_hba *phba,
				struct be_dma_mem *nonemb_cmd, void *resp_buf,
				int resp_buf_len)
{
	struct be_ctrl_info *ctrl = &phba->ctrl;
	struct be_mcc_wrb *wrb = wrb_from_mccq(phba);
	struct be_sge *sge;
	unsigned int tag;
	int rc = 0;

	spin_lock(&ctrl->mbox_lock);
	tag = alloc_mcc_tag(phba);
	if (!tag) {
		spin_unlock(&ctrl->mbox_lock);
		rc = -ENOMEM;
		goto free_cmd;
	}
	memset(wrb, 0, sizeof(*wrb));
	wrb->tag0 |= tag;
	sge = nonembedded_sgl(wrb);

	be_wrb_hdr_prepare(wrb, nonemb_cmd->size, false, 1);
	sge->pa_hi = cpu_to_le32(upper_32_bits(nonemb_cmd->dma));
	sge->pa_lo = cpu_to_le32(lower_32_bits(nonemb_cmd->dma));
	sge->len = cpu_to_le32(nonemb_cmd->size);

	be_mcc_notify(phba);
	spin_unlock(&ctrl->mbox_lock);

	rc = beiscsi_mccq_compl(phba, tag, NULL, nonemb_cmd->va);
	if (rc) {
		beiscsi_log(phba, KERN_ERR,
			    BEISCSI_LOG_CONFIG | BEISCSI_LOG_MBOX,
			    "BG_%d : mgmt_exec_nonemb_cmd Failed status\n");

		rc = -EIO;
		goto free_cmd;
	}

	if (resp_buf)
		memcpy(resp_buf, nonemb_cmd->va, resp_buf_len);

free_cmd:
	pci_free_consistent(ctrl->pdev, nonemb_cmd->size,
			    nonemb_cmd->va, nonemb_cmd->dma);
	return rc;
}