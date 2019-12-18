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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  temp_event_data ;
struct temp_event {scalar_t__ data; int /*<<< orphan*/  event_code; int /*<<< orphan*/  event_type; } ;
struct lpfc_vport {int dummy; } ;
struct lpfc_sli_ring {int dummy; } ;
struct lpfc_sli {size_t fcp_ring; struct lpfc_sli_ring* ring; int /*<<< orphan*/  sli_flag; } ;
struct lpfc_hba {int hba_flag; int work_hs; int /*<<< orphan*/ * work_status; int /*<<< orphan*/  hbalock; int /*<<< orphan*/  over_temp_state; struct lpfc_vport* pport; scalar_t__ MBslimaddr; int /*<<< orphan*/  cfg_enable_hba_reset; int /*<<< orphan*/  pcidev; struct lpfc_sli sli; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  event_data ;

/* Variables and functions */
 int DEFER_ERATT ; 
 scalar_t__ FC_REG_DUMP_EVENT ; 
 int /*<<< orphan*/  FC_REG_TEMPERATURE_EVENT ; 
 int /*<<< orphan*/  HBA_OVER_TEMP ; 
 int HS_CRIT_TEMP ; 
 int HS_FFER6 ; 
 int HS_FFER8 ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LOG_LINK_EVENT ; 
 int /*<<< orphan*/  LPFC_CRIT_TEMP ; 
 int /*<<< orphan*/  LPFC_MBX_NO_WAIT ; 
 int /*<<< orphan*/  LPFC_NL_VENDOR_ID ; 
 int /*<<< orphan*/  LPFC_SLI_ACTIVE ; 
 scalar_t__ TEMPERATURE_OFFSET ; 
 int /*<<< orphan*/  fc_get_event_number () ; 
 int /*<<< orphan*/  fc_host_post_vendor_event (struct Scsi_Host*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_board_errevt_to_mgmt (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_handle_deferred_eratt (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_offline (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_offline_eratt (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_offline_prep (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 scalar_t__ lpfc_online (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,...) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_sli_abort_iocb_ring (struct lpfc_hba*,struct lpfc_sli_ring*) ; 
 int /*<<< orphan*/  lpfc_sli_brdrestart (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_unblock_mgmt_io (struct lpfc_hba*) ; 
 scalar_t__ pci_channel_offline (int /*<<< orphan*/ ) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lpfc_handle_eratt_s3(struct lpfc_hba *phba)
{
	struct lpfc_vport *vport = phba->pport;
	struct lpfc_sli   *psli = &phba->sli;
	struct lpfc_sli_ring  *pring;
	uint32_t event_data;
	unsigned long temperature;
	struct temp_event temp_event_data;
	struct Scsi_Host  *shost;

	/* If the pci channel is offline, ignore possible errors,
	 * since we cannot communicate with the pci card anyway.
	 */
	if (pci_channel_offline(phba->pcidev)) {
		spin_lock_irq(&phba->hbalock);
		phba->hba_flag &= ~DEFER_ERATT;
		spin_unlock_irq(&phba->hbalock);
		return;
	}

	/* If resets are disabled then leave the HBA alone and return */
	if (!phba->cfg_enable_hba_reset)
		return;

	/* Send an internal error event to mgmt application */
	lpfc_board_errevt_to_mgmt(phba);

	if (phba->hba_flag & DEFER_ERATT)
		lpfc_handle_deferred_eratt(phba);

	if ((phba->work_hs & HS_FFER6) || (phba->work_hs & HS_FFER8)) {
		if (phba->work_hs & HS_FFER6)
			/* Re-establishing Link */
			lpfc_printf_log(phba, KERN_INFO, LOG_LINK_EVENT,
					"1301 Re-establishing Link "
					"Data: x%x x%x x%x\n",
					phba->work_hs, phba->work_status[0],
					phba->work_status[1]);
		if (phba->work_hs & HS_FFER8)
			/* Device Zeroization */
			lpfc_printf_log(phba, KERN_INFO, LOG_LINK_EVENT,
					"2861 Host Authentication device "
					"zeroization Data:x%x x%x x%x\n",
					phba->work_hs, phba->work_status[0],
					phba->work_status[1]);

		spin_lock_irq(&phba->hbalock);
		psli->sli_flag &= ~LPFC_SLI_ACTIVE;
		spin_unlock_irq(&phba->hbalock);

		/*
		* Firmware stops when it triggled erratt with HS_FFER6.
		* That could cause the I/Os dropped by the firmware.
		* Error iocb (I/O) on txcmplq and let the SCSI layer
		* retry it after re-establishing link.
		*/
		pring = &psli->ring[psli->fcp_ring];
		lpfc_sli_abort_iocb_ring(phba, pring);

		/*
		 * There was a firmware error.  Take the hba offline and then
		 * attempt to restart it.
		 */
		lpfc_offline_prep(phba, LPFC_MBX_NO_WAIT);
		lpfc_offline(phba);
		lpfc_sli_brdrestart(phba);
		if (lpfc_online(phba) == 0) {	/* Initialize the HBA */
			lpfc_unblock_mgmt_io(phba);
			return;
		}
		lpfc_unblock_mgmt_io(phba);
	} else if (phba->work_hs & HS_CRIT_TEMP) {
		temperature = readl(phba->MBslimaddr + TEMPERATURE_OFFSET);
		temp_event_data.event_type = FC_REG_TEMPERATURE_EVENT;
		temp_event_data.event_code = LPFC_CRIT_TEMP;
		temp_event_data.data = (uint32_t)temperature;

		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0406 Adapter maximum temperature exceeded "
				"(%ld), taking this port offline "
				"Data: x%x x%x x%x\n",
				temperature, phba->work_hs,
				phba->work_status[0], phba->work_status[1]);

		shost = lpfc_shost_from_vport(phba->pport);
		fc_host_post_vendor_event(shost, fc_get_event_number(),
					  sizeof(temp_event_data),
					  (char *) &temp_event_data,
					  LPFC_NL_VENDOR_ID);

		spin_lock_irq(&phba->hbalock);
		phba->over_temp_state = HBA_OVER_TEMP;
		spin_unlock_irq(&phba->hbalock);
		lpfc_offline_eratt(phba);

	} else {
		/* The if clause above forces this code path when the status
		 * failure is a value other than FFER6. Do not call the offline
		 * twice. This is the adapter hardware error path.
		 */
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0457 Adapter Hardware Error "
				"Data: x%x x%x x%x\n",
				phba->work_hs,
				phba->work_status[0], phba->work_status[1]);

		event_data = FC_REG_DUMP_EVENT;
		shost = lpfc_shost_from_vport(vport);
		fc_host_post_vendor_event(shost, fc_get_event_number(),
				sizeof(event_data), (char *) &event_data,
				LPFC_NL_VENDOR_ID);

		lpfc_offline_eratt(phba);
	}
	return;
}