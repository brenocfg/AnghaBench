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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {int fcf_flag; } ;
struct lpfc_hba {scalar_t__ link_state; scalar_t__ fcoe_eventtag; scalar_t__ fcoe_eventtag_at_fcf_scan; int hba_flag; int /*<<< orphan*/  hbalock; TYPE_1__ fcf; } ;

/* Variables and functions */
 int FCF_AVAILABLE ; 
 int FCF_DISCOVERY ; 
 int FCF_REDISC_FOV ; 
 int FCF_REGISTERED ; 
 int FCF_RR_INPROG ; 
 int FCF_TS_INPROG ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int LOG_DISCOVERY ; 
 int LOG_FIP ; 
 int /*<<< orphan*/  LPFC_FCOE_FCF_GET_FIRST ; 
 scalar_t__ LPFC_LINK_UP ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  lpfc_sli4_fcf_scan_read_fcf_rec (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli4_unregister_fcf (struct lpfc_hba*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int
lpfc_check_pending_fcoe_event(struct lpfc_hba *phba, uint8_t unreg_fcf)
{
	/*
	 * If the Link is up and no FCoE events while in the
	 * FCF discovery, no need to restart FCF discovery.
	 */
	if ((phba->link_state  >= LPFC_LINK_UP) &&
	    (phba->fcoe_eventtag == phba->fcoe_eventtag_at_fcf_scan))
		return 0;

	lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
			"2768 Pending link or FCF event during current "
			"handling of the previous event: link_state:x%x, "
			"evt_tag_at_scan:x%x, evt_tag_current:x%x\n",
			phba->link_state, phba->fcoe_eventtag_at_fcf_scan,
			phba->fcoe_eventtag);

	spin_lock_irq(&phba->hbalock);
	phba->fcf.fcf_flag &= ~FCF_AVAILABLE;
	spin_unlock_irq(&phba->hbalock);

	if (phba->link_state >= LPFC_LINK_UP) {
		lpfc_printf_log(phba, KERN_INFO, LOG_FIP | LOG_DISCOVERY,
				"2780 Restart FCF table scan due to "
				"pending FCF event:evt_tag_at_scan:x%x, "
				"evt_tag_current:x%x\n",
				phba->fcoe_eventtag_at_fcf_scan,
				phba->fcoe_eventtag);
		lpfc_sli4_fcf_scan_read_fcf_rec(phba, LPFC_FCOE_FCF_GET_FIRST);
	} else {
		/*
		 * Do not continue FCF discovery and clear FCF_TS_INPROG
		 * flag
		 */
		lpfc_printf_log(phba, KERN_INFO, LOG_FIP | LOG_DISCOVERY,
				"2833 Stop FCF discovery process due to link "
				"state change (x%x)\n", phba->link_state);
		spin_lock_irq(&phba->hbalock);
		phba->hba_flag &= ~(FCF_TS_INPROG | FCF_RR_INPROG);
		phba->fcf.fcf_flag &= ~(FCF_REDISC_FOV | FCF_DISCOVERY);
		spin_unlock_irq(&phba->hbalock);
	}

	/* Unregister the currently registered FCF if required */
	if (unreg_fcf) {
		spin_lock_irq(&phba->hbalock);
		phba->fcf.fcf_flag &= ~FCF_REGISTERED;
		spin_unlock_irq(&phba->hbalock);
		lpfc_sli4_unregister_fcf(phba);
	}
	return 1;
}