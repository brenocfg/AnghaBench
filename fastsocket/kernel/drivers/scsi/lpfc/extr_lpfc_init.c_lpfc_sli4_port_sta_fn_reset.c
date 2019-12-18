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
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_hba {int /*<<< orphan*/  intr_mode; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LPFC_INTR_ERROR ; 
 int /*<<< orphan*/  lpfc_offline (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_offline_prep (struct lpfc_hba*,int) ; 
 int lpfc_online (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_sli4_disable_intr (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_enable_intr (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int lpfc_sli4_pdev_status_reg_wait (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_brdrestart (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_unblock_mgmt_io (struct lpfc_hba*) ; 

__attribute__((used)) static int
lpfc_sli4_port_sta_fn_reset(struct lpfc_hba *phba, int mbx_action)
{
	int rc;
	uint32_t intr_mode;

	/*
	 * On error status condition, driver need to wait for port
	 * ready before performing reset.
	 */
	rc = lpfc_sli4_pdev_status_reg_wait(phba);
	if (!rc) {
		/* need reset: attempt for port recovery */
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"2887 Reset Needed: Attempting Port "
				"Recovery...\n");
		lpfc_offline_prep(phba, mbx_action);
		lpfc_offline(phba);
		/* release interrupt for possible resource change */
		lpfc_sli4_disable_intr(phba);
		lpfc_sli_brdrestart(phba);
		/* request and enable interrupt */
		intr_mode = lpfc_sli4_enable_intr(phba, phba->intr_mode);
		if (intr_mode == LPFC_INTR_ERROR) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"3175 Failed to enable interrupt\n");
			return -EIO;
		} else {
			phba->intr_mode = intr_mode;
		}
		rc = lpfc_online(phba);
		if (rc == 0)
			lpfc_unblock_mgmt_io(phba);
	}
	return rc;
}