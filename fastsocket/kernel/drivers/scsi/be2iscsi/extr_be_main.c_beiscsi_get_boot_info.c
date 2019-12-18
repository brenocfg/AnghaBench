#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mgmt_session_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;
struct beiscsi_hba {TYPE_1__ ctrl; int /*<<< orphan*/  boot_sess; } ;
struct be_dma_mem {int /*<<< orphan*/  dma; struct be_cmd_get_session_resp* va; int /*<<< orphan*/  size; } ;
struct be_cmd_get_session_resp {int /*<<< orphan*/  session_info; } ;

/* Variables and functions */
 int BEISCSI_LOG_CONFIG ; 
 int BEISCSI_LOG_INIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int be_mgmt_get_boot_shandle (struct beiscsi_hba*,unsigned int*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int,char*) ; 
 int beiscsi_mccq_compl (struct beiscsi_hba*,unsigned int,int /*<<< orphan*/ *,struct be_cmd_get_session_resp*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct be_cmd_get_session_resp*,int /*<<< orphan*/ ,int) ; 
 unsigned int mgmt_get_session_info (struct beiscsi_hba*,unsigned int,struct be_dma_mem*) ; 
 struct be_cmd_get_session_resp* pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct be_cmd_get_session_resp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int beiscsi_get_boot_info(struct beiscsi_hba *phba)
{
	struct be_cmd_get_session_resp *session_resp;
	struct be_dma_mem nonemb_cmd;
	unsigned int tag;
	unsigned int s_handle;
	int ret = -ENOMEM;

	/* Get the session handle of the boot target */
	ret = be_mgmt_get_boot_shandle(phba, &s_handle);
	if (ret) {
		beiscsi_log(phba, KERN_ERR,
			    BEISCSI_LOG_INIT | BEISCSI_LOG_CONFIG,
			    "BM_%d : No boot session\n");
		return ret;
	}
	nonemb_cmd.va = pci_alloc_consistent(phba->ctrl.pdev,
				sizeof(*session_resp),
				&nonemb_cmd.dma);
	if (nonemb_cmd.va == NULL) {
		beiscsi_log(phba, KERN_ERR,
			    BEISCSI_LOG_INIT | BEISCSI_LOG_CONFIG,
			    "BM_%d : Failed to allocate memory for"
			    "beiscsi_get_session_info\n");

		return -ENOMEM;
	}

	memset(nonemb_cmd.va, 0, sizeof(*session_resp));
	tag = mgmt_get_session_info(phba, s_handle,
				    &nonemb_cmd);
	if (!tag) {
		beiscsi_log(phba, KERN_ERR,
			    BEISCSI_LOG_INIT | BEISCSI_LOG_CONFIG,
			    "BM_%d : beiscsi_get_session_info"
			    " Failed\n");

		goto boot_freemem;
	}

	ret = beiscsi_mccq_compl(phba, tag, NULL, nonemb_cmd.va);
	if (ret) {
		beiscsi_log(phba, KERN_ERR,
			    BEISCSI_LOG_INIT | BEISCSI_LOG_CONFIG,
			    "BM_%d : beiscsi_get_session_info Failed");
		goto boot_freemem;
	}

	session_resp = nonemb_cmd.va ;

	memcpy(&phba->boot_sess, &session_resp->session_info,
	       sizeof(struct mgmt_session_info));
	ret = 0;

boot_freemem:
	pci_free_consistent(phba->ctrl.pdev, nonemb_cmd.size,
		    nonemb_cmd.va, nonemb_cmd.dma);
	return ret;
}