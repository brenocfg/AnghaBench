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
typedef  int uint32_t ;
struct lpfc_hba {int link_flag; int hba_flag; int sli_rev; int /*<<< orphan*/  hbalock; int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int DEFER_ERATT ; 
 int HBA_ERATT_HANDLED ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
#define  LPFC_SLI_REV2 130 
#define  LPFC_SLI_REV3 129 
#define  LPFC_SLI_REV4 128 
 int LS_IGNORE_ERATT ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int lpfc_sli4_eratt_read (struct lpfc_hba*) ; 
 int lpfc_sli_eratt_read (struct lpfc_hba*) ; 
 int pci_channel_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int
lpfc_sli_check_eratt(struct lpfc_hba *phba)
{
	uint32_t ha_copy;

	/* If somebody is waiting to handle an eratt, don't process it
	 * here. The brdkill function will do this.
	 */
	if (phba->link_flag & LS_IGNORE_ERATT)
		return 0;

	/* Check if interrupt handler handles this ERATT */
	spin_lock_irq(&phba->hbalock);
	if (phba->hba_flag & HBA_ERATT_HANDLED) {
		/* Interrupt handler has handled ERATT */
		spin_unlock_irq(&phba->hbalock);
		return 0;
	}

	/*
	 * If there is deferred error attention, do not check for error
	 * attention
	 */
	if (unlikely(phba->hba_flag & DEFER_ERATT)) {
		spin_unlock_irq(&phba->hbalock);
		return 0;
	}

	/* If PCI channel is offline, don't process it */
	if (unlikely(pci_channel_offline(phba->pcidev))) {
		spin_unlock_irq(&phba->hbalock);
		return 0;
	}

	switch (phba->sli_rev) {
	case LPFC_SLI_REV2:
	case LPFC_SLI_REV3:
		/* Read chip Host Attention (HA) register */
		ha_copy = lpfc_sli_eratt_read(phba);
		break;
	case LPFC_SLI_REV4:
		/* Read device Uncoverable Error (UERR) registers */
		ha_copy = lpfc_sli4_eratt_read(phba);
		break;
	default:
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0299 Invalid SLI revision (%d)\n",
				phba->sli_rev);
		ha_copy = 0;
		break;
	}
	spin_unlock_irq(&phba->hbalock);

	return ha_copy;
}