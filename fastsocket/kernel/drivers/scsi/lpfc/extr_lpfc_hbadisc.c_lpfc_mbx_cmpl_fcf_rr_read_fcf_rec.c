#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_7__ {scalar_t__ fcf_indx; } ;
struct TYPE_6__ {scalar_t__ fcf_indx; } ;
struct TYPE_5__ {TYPE_3__ failover_rec; TYPE_2__ current_rec; int /*<<< orphan*/  fcf_flag; } ;
struct lpfc_hba {scalar_t__ link_state; TYPE_1__ fcf; int /*<<< orphan*/  hbalock; int /*<<< orphan*/  pport; int /*<<< orphan*/  hba_flag; } ;
struct lpfc_fcf_rec {int dummy; } ;
struct fcf_record {int dummy; } ;
typedef  int /*<<< orphan*/  LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  BOOT_ENABLE ; 
 int /*<<< orphan*/  FCF_DISCOVERY ; 
 int /*<<< orphan*/  FCF_RR_INPROG ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_FIP ; 
 scalar_t__ LPFC_LINK_UP ; 
 int /*<<< orphan*/  __lpfc_update_fcf_record (struct lpfc_hba*,TYPE_3__*,struct fcf_record*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,struct fcf_record*) ; 
 int /*<<< orphan*/  lpfc_fcf_record_fcf_index ; 
 int /*<<< orphan*/  lpfc_issue_init_vfi (int /*<<< orphan*/ ) ; 
 int lpfc_match_fcf_conn_list (struct lpfc_hba*,struct fcf_record*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  lpfc_register_fcf (struct lpfc_hba*) ; 
 struct fcf_record* lpfc_sli4_fcf_rec_mbox_parse (struct lpfc_hba*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  lpfc_sli4_fcf_rr_index_clear (struct lpfc_hba*,scalar_t__) ; 
 scalar_t__ lpfc_sli4_fcf_rr_next_index_get (struct lpfc_hba*) ; 
 int lpfc_sli4_fcf_rr_next_proc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_sli4_log_fcf_record_info (struct lpfc_hba*,struct fcf_record*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_sli4_mbox_cmd_free (struct lpfc_hba*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_unregister_fcf (struct lpfc_hba*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void
lpfc_mbx_cmpl_fcf_rr_read_fcf_rec(struct lpfc_hba *phba, LPFC_MBOXQ_t *mboxq)
{
	struct fcf_record *new_fcf_record;
	uint32_t boot_flag, addr_mode;
	uint16_t next_fcf_index, fcf_index;
	uint16_t current_fcf_index;
	uint16_t vlan_id;
	int rc;

	/* If link state is not up, stop the roundrobin failover process */
	if (phba->link_state < LPFC_LINK_UP) {
		spin_lock_irq(&phba->hbalock);
		phba->fcf.fcf_flag &= ~FCF_DISCOVERY;
		phba->hba_flag &= ~FCF_RR_INPROG;
		spin_unlock_irq(&phba->hbalock);
		goto out;
	}

	/* Parse the FCF record from the non-embedded mailbox command */
	new_fcf_record = lpfc_sli4_fcf_rec_mbox_parse(phba, mboxq,
						      &next_fcf_index);
	if (!new_fcf_record) {
		lpfc_printf_log(phba, KERN_WARNING, LOG_FIP,
				"2766 Mailbox command READ_FCF_RECORD "
				"failed to retrieve a FCF record.\n");
		goto error_out;
	}

	/* Get the needed parameters from FCF record */
	rc = lpfc_match_fcf_conn_list(phba, new_fcf_record, &boot_flag,
				      &addr_mode, &vlan_id);

	/* Log the FCF record information if turned on */
	lpfc_sli4_log_fcf_record_info(phba, new_fcf_record, vlan_id,
				      next_fcf_index);

	fcf_index = bf_get(lpfc_fcf_record_fcf_index, new_fcf_record);
	if (!rc) {
		lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
				"2848 Remove ineligible FCF (x%x) from "
				"from roundrobin bmask\n", fcf_index);
		/* Clear roundrobin bmask bit for ineligible FCF */
		lpfc_sli4_fcf_rr_index_clear(phba, fcf_index);
		/* Perform next round of roundrobin FCF failover */
		fcf_index = lpfc_sli4_fcf_rr_next_index_get(phba);
		rc = lpfc_sli4_fcf_rr_next_proc(phba->pport, fcf_index);
		if (rc)
			goto out;
		goto error_out;
	}

	if (fcf_index == phba->fcf.current_rec.fcf_indx) {
		lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
				"2760 Perform FLOGI roundrobin FCF failover: "
				"FCF (x%x) back to FCF (x%x)\n",
				phba->fcf.current_rec.fcf_indx, fcf_index);
		/* Wait 500 ms before retrying FLOGI to current FCF */
		msleep(500);
		lpfc_issue_init_vfi(phba->pport);
		goto out;
	}

	/* Upload new FCF record to the failover FCF record */
	lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
			"2834 Update current FCF (x%x) with new FCF (x%x)\n",
			phba->fcf.failover_rec.fcf_indx, fcf_index);
	spin_lock_irq(&phba->hbalock);
	__lpfc_update_fcf_record(phba, &phba->fcf.failover_rec,
				 new_fcf_record, addr_mode, vlan_id,
				 (boot_flag ? BOOT_ENABLE : 0));
	spin_unlock_irq(&phba->hbalock);

	current_fcf_index = phba->fcf.current_rec.fcf_indx;

	/* Unregister the current in-use FCF record */
	lpfc_unregister_fcf(phba);

	/* Replace in-use record with the new record */
	memcpy(&phba->fcf.current_rec, &phba->fcf.failover_rec,
	       sizeof(struct lpfc_fcf_rec));

	lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
			"2783 Perform FLOGI roundrobin FCF failover: FCF "
			"(x%x) to FCF (x%x)\n", current_fcf_index, fcf_index);

error_out:
	lpfc_register_fcf(phba);
out:
	lpfc_sli4_mbox_cmd_free(phba, mboxq);
}