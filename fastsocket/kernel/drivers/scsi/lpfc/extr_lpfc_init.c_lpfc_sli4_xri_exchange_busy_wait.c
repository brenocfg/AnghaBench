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
struct TYPE_2__ {int /*<<< orphan*/  lpfc_abts_els_sgl_list; int /*<<< orphan*/  lpfc_abts_scsi_buf_list; } ;
struct lpfc_hba {TYPE_1__ sli4_hba; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 scalar_t__ LPFC_XRI_EXCH_BUSY_WAIT_T1 ; 
 scalar_t__ LPFC_XRI_EXCH_BUSY_WAIT_T2 ; 
 int LPFC_XRI_EXCH_BUSY_WAIT_TMO ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 

__attribute__((used)) static void
lpfc_sli4_xri_exchange_busy_wait(struct lpfc_hba *phba)
{
	int wait_time = 0;
	int fcp_xri_cmpl = list_empty(&phba->sli4_hba.lpfc_abts_scsi_buf_list);
	int els_xri_cmpl = list_empty(&phba->sli4_hba.lpfc_abts_els_sgl_list);

	while (!fcp_xri_cmpl || !els_xri_cmpl) {
		if (wait_time > LPFC_XRI_EXCH_BUSY_WAIT_TMO) {
			if (!fcp_xri_cmpl)
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
						"2877 FCP XRI exchange busy "
						"wait time: %d seconds.\n",
						wait_time/1000);
			if (!els_xri_cmpl)
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
						"2878 ELS XRI exchange busy "
						"wait time: %d seconds.\n",
						wait_time/1000);
			msleep(LPFC_XRI_EXCH_BUSY_WAIT_T2);
			wait_time += LPFC_XRI_EXCH_BUSY_WAIT_T2;
		} else {
			msleep(LPFC_XRI_EXCH_BUSY_WAIT_T1);
			wait_time += LPFC_XRI_EXCH_BUSY_WAIT_T1;
		}
		fcp_xri_cmpl =
			list_empty(&phba->sli4_hba.lpfc_abts_scsi_buf_list);
		els_xri_cmpl =
			list_empty(&phba->sli4_hba.lpfc_abts_els_sgl_list);
	}
}