#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct lpfc_fcf_rec {scalar_t__ fcf_indx; int flag; scalar_t__ priority; } ;
struct TYPE_4__ {int fcf_flag; int eligible_fcf_cnt; struct lpfc_fcf_rec current_rec; struct lpfc_fcf_rec failover_rec; } ;
struct lpfc_hba {int hba_flag; scalar_t__ cfg_fcf_failover_policy; int /*<<< orphan*/  hbalock; TYPE_2__ fcf; int /*<<< orphan*/  fcoe_eventtag_at_fcf_scan; TYPE_1__* pport; } ;
struct fcf_record {scalar_t__ fip_priority; } ;
struct TYPE_3__ {int /*<<< orphan*/  fc_flag; int /*<<< orphan*/  port_state; } ;
typedef  int /*<<< orphan*/  LPFC_MBOXQ_t ;

/* Variables and functions */
 int BOOT_ENABLE ; 
 int FCF_AVAILABLE ; 
 int FCF_IN_USE ; 
 int FCF_REDISC_EVT ; 
 int FCF_REDISC_FOV ; 
 int FCF_REDISC_PEND ; 
 int FCF_TS_INPROG ; 
 int HBA_DEVLOSS_TMO ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_FIP ; 
 scalar_t__ LPFC_FCF_FOV ; 
 scalar_t__ LPFC_FCOE_FCF_GET_FIRST ; 
 scalar_t__ LPFC_FCOE_FCF_NEXT_NONE ; 
 scalar_t__ LPFC_FCOE_IGNORE_VID ; 
 int /*<<< orphan*/  LPFC_SKIP_UNREG_FCF ; 
 int RECORD_VALID ; 
 int /*<<< orphan*/  __lpfc_sli4_stop_fcf_redisc_wait_timer (struct lpfc_hba*) ; 
 int /*<<< orphan*/  __lpfc_update_fcf_record (struct lpfc_hba*,struct lpfc_fcf_rec*,struct fcf_record*,scalar_t__,scalar_t__,int) ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,struct fcf_record*) ; 
 int jiffies ; 
 scalar_t__ lpfc_check_pending_fcoe_event (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_fcf_record_fcf_avail ; 
 int /*<<< orphan*/  lpfc_fcf_record_fcf_index ; 
 int /*<<< orphan*/  lpfc_fcf_record_fcf_sol ; 
 int /*<<< orphan*/  lpfc_fcf_record_fcf_valid ; 
 int lpfc_match_fcf_conn_list (struct lpfc_hba*,struct fcf_record*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  lpfc_register_fcf (struct lpfc_hba*) ; 
 int lpfc_sli4_fcf_pri_list_add (struct lpfc_hba*,scalar_t__,struct fcf_record*) ; 
 int /*<<< orphan*/  lpfc_sli4_fcf_pri_list_del (struct lpfc_hba*,scalar_t__) ; 
 struct fcf_record* lpfc_sli4_fcf_rec_mbox_parse (struct lpfc_hba*,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ lpfc_sli4_fcf_record_match (struct lpfc_hba*,struct lpfc_fcf_rec*,struct fcf_record*,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_sli4_fcf_scan_read_fcf_rec (struct lpfc_hba*,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_sli4_log_fcf_record_info (struct lpfc_hba*,struct fcf_record*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_sli4_mbox_cmd_free (struct lpfc_hba*,int /*<<< orphan*/ *) ; 
 int lpfc_sli4_new_fcf_random_select (struct lpfc_hba*,int) ; 
 int /*<<< orphan*/  lpfc_unregister_fcf (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_unregister_fcf_rescan (struct lpfc_hba*) ; 
 int /*<<< orphan*/  memcpy (struct lpfc_fcf_rec*,struct lpfc_fcf_rec*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srandom32 (scalar_t__) ; 

void
lpfc_mbx_cmpl_fcf_scan_read_fcf_rec(struct lpfc_hba *phba, LPFC_MBOXQ_t *mboxq)
{
	struct fcf_record *new_fcf_record;
	uint32_t boot_flag, addr_mode;
	uint16_t fcf_index, next_fcf_index;
	struct lpfc_fcf_rec *fcf_rec = NULL;
	uint16_t vlan_id;
	uint32_t seed;
	bool select_new_fcf;
	int rc;

	/* If there is pending FCoE event restart FCF table scan */
	if (lpfc_check_pending_fcoe_event(phba, LPFC_SKIP_UNREG_FCF)) {
		lpfc_sli4_mbox_cmd_free(phba, mboxq);
		return;
	}

	/* Parse the FCF record from the non-embedded mailbox command */
	new_fcf_record = lpfc_sli4_fcf_rec_mbox_parse(phba, mboxq,
						      &next_fcf_index);
	if (!new_fcf_record) {
		lpfc_printf_log(phba, KERN_ERR, LOG_FIP,
				"2765 Mailbox command READ_FCF_RECORD "
				"failed to retrieve a FCF record.\n");
		/* Let next new FCF event trigger fast failover */
		spin_lock_irq(&phba->hbalock);
		phba->hba_flag &= ~FCF_TS_INPROG;
		spin_unlock_irq(&phba->hbalock);
		lpfc_sli4_mbox_cmd_free(phba, mboxq);
		return;
	}

	/* Check the FCF record against the connection list */
	rc = lpfc_match_fcf_conn_list(phba, new_fcf_record, &boot_flag,
				      &addr_mode, &vlan_id);

	/* Log the FCF record information if turned on */
	lpfc_sli4_log_fcf_record_info(phba, new_fcf_record, vlan_id,
				      next_fcf_index);

	/*
	 * If the fcf record does not match with connect list entries
	 * read the next entry; otherwise, this is an eligible FCF
	 * record for roundrobin FCF failover.
	 */
	if (!rc) {
		lpfc_sli4_fcf_pri_list_del(phba,
					bf_get(lpfc_fcf_record_fcf_index,
					       new_fcf_record));
		lpfc_printf_log(phba, KERN_WARNING, LOG_FIP,
				"2781 FCF (x%x) failed connection "
				"list check: (x%x/x%x/%x)\n",
				bf_get(lpfc_fcf_record_fcf_index,
				       new_fcf_record),
				bf_get(lpfc_fcf_record_fcf_avail,
				       new_fcf_record),
				bf_get(lpfc_fcf_record_fcf_valid,
				       new_fcf_record),
				bf_get(lpfc_fcf_record_fcf_sol,
				       new_fcf_record));
		if ((phba->fcf.fcf_flag & FCF_IN_USE) &&
		    lpfc_sli4_fcf_record_match(phba, &phba->fcf.current_rec,
		    new_fcf_record, LPFC_FCOE_IGNORE_VID)) {
			if (bf_get(lpfc_fcf_record_fcf_index, new_fcf_record) !=
			    phba->fcf.current_rec.fcf_indx) {
				lpfc_printf_log(phba, KERN_ERR, LOG_FIP,
					"2862 FCF (x%x) matches property "
					"of in-use FCF (x%x)\n",
					bf_get(lpfc_fcf_record_fcf_index,
					       new_fcf_record),
					phba->fcf.current_rec.fcf_indx);
				goto read_next_fcf;
			}
			/*
			 * In case the current in-use FCF record becomes
			 * invalid/unavailable during FCF discovery that
			 * was not triggered by fast FCF failover process,
			 * treat it as fast FCF failover.
			 */
			if (!(phba->fcf.fcf_flag & FCF_REDISC_PEND) &&
			    !(phba->fcf.fcf_flag & FCF_REDISC_FOV)) {
				lpfc_printf_log(phba, KERN_WARNING, LOG_FIP,
						"2835 Invalid in-use FCF "
						"(x%x), enter FCF failover "
						"table scan.\n",
						phba->fcf.current_rec.fcf_indx);
				spin_lock_irq(&phba->hbalock);
				phba->fcf.fcf_flag |= FCF_REDISC_FOV;
				spin_unlock_irq(&phba->hbalock);
				lpfc_sli4_mbox_cmd_free(phba, mboxq);
				lpfc_sli4_fcf_scan_read_fcf_rec(phba,
						LPFC_FCOE_FCF_GET_FIRST);
				return;
			}
		}
		goto read_next_fcf;
	} else {
		fcf_index = bf_get(lpfc_fcf_record_fcf_index, new_fcf_record);
		rc = lpfc_sli4_fcf_pri_list_add(phba, fcf_index,
							new_fcf_record);
		if (rc)
			goto read_next_fcf;
	}

	/*
	 * If this is not the first FCF discovery of the HBA, use last
	 * FCF record for the discovery. The condition that a rescan
	 * matches the in-use FCF record: fabric name, switch name, mac
	 * address, and vlan_id.
	 */
	spin_lock_irq(&phba->hbalock);
	if (phba->fcf.fcf_flag & FCF_IN_USE) {
		if (phba->cfg_fcf_failover_policy == LPFC_FCF_FOV &&
			lpfc_sli4_fcf_record_match(phba, &phba->fcf.current_rec,
		    new_fcf_record, vlan_id)) {
			if (bf_get(lpfc_fcf_record_fcf_index, new_fcf_record) ==
			    phba->fcf.current_rec.fcf_indx) {
				phba->fcf.fcf_flag |= FCF_AVAILABLE;
				if (phba->fcf.fcf_flag & FCF_REDISC_PEND)
					/* Stop FCF redisc wait timer */
					__lpfc_sli4_stop_fcf_redisc_wait_timer(
									phba);
				else if (phba->fcf.fcf_flag & FCF_REDISC_FOV)
					/* Fast failover, mark completed */
					phba->fcf.fcf_flag &= ~FCF_REDISC_FOV;
				spin_unlock_irq(&phba->hbalock);
				lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
						"2836 New FCF matches in-use "
						"FCF (x%x), port_state:x%x, "
						"fc_flag:x%x\n",
						phba->fcf.current_rec.fcf_indx,
						phba->pport->port_state,
						phba->pport->fc_flag);
				goto out;
			} else
				lpfc_printf_log(phba, KERN_ERR, LOG_FIP,
					"2863 New FCF (x%x) matches "
					"property of in-use FCF (x%x)\n",
					bf_get(lpfc_fcf_record_fcf_index,
					       new_fcf_record),
					phba->fcf.current_rec.fcf_indx);
		}
		/*
		 * Read next FCF record from HBA searching for the matching
		 * with in-use record only if not during the fast failover
		 * period. In case of fast failover period, it shall try to
		 * determine whether the FCF record just read should be the
		 * next candidate.
		 */
		if (!(phba->fcf.fcf_flag & FCF_REDISC_FOV)) {
			spin_unlock_irq(&phba->hbalock);
			goto read_next_fcf;
		}
	}
	/*
	 * Update on failover FCF record only if it's in FCF fast-failover
	 * period; otherwise, update on current FCF record.
	 */
	if (phba->fcf.fcf_flag & FCF_REDISC_FOV)
		fcf_rec = &phba->fcf.failover_rec;
	else
		fcf_rec = &phba->fcf.current_rec;

	if (phba->fcf.fcf_flag & FCF_AVAILABLE) {
		/*
		 * If the driver FCF record does not have boot flag
		 * set and new hba fcf record has boot flag set, use
		 * the new hba fcf record.
		 */
		if (boot_flag && !(fcf_rec->flag & BOOT_ENABLE)) {
			/* Choose this FCF record */
			lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
					"2837 Update current FCF record "
					"(x%x) with new FCF record (x%x)\n",
					fcf_rec->fcf_indx,
					bf_get(lpfc_fcf_record_fcf_index,
					new_fcf_record));
			__lpfc_update_fcf_record(phba, fcf_rec, new_fcf_record,
					addr_mode, vlan_id, BOOT_ENABLE);
			spin_unlock_irq(&phba->hbalock);
			goto read_next_fcf;
		}
		/*
		 * If the driver FCF record has boot flag set and the
		 * new hba FCF record does not have boot flag, read
		 * the next FCF record.
		 */
		if (!boot_flag && (fcf_rec->flag & BOOT_ENABLE)) {
			spin_unlock_irq(&phba->hbalock);
			goto read_next_fcf;
		}
		/*
		 * If the new hba FCF record has lower priority value
		 * than the driver FCF record, use the new record.
		 */
		if (new_fcf_record->fip_priority < fcf_rec->priority) {
			/* Choose the new FCF record with lower priority */
			lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
					"2838 Update current FCF record "
					"(x%x) with new FCF record (x%x)\n",
					fcf_rec->fcf_indx,
					bf_get(lpfc_fcf_record_fcf_index,
					       new_fcf_record));
			__lpfc_update_fcf_record(phba, fcf_rec, new_fcf_record,
					addr_mode, vlan_id, 0);
			/* Reset running random FCF selection count */
			phba->fcf.eligible_fcf_cnt = 1;
		} else if (new_fcf_record->fip_priority == fcf_rec->priority) {
			/* Update running random FCF selection count */
			phba->fcf.eligible_fcf_cnt++;
			select_new_fcf = lpfc_sli4_new_fcf_random_select(phba,
						phba->fcf.eligible_fcf_cnt);
			if (select_new_fcf) {
				lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
					"2839 Update current FCF record "
					"(x%x) with new FCF record (x%x)\n",
					fcf_rec->fcf_indx,
					bf_get(lpfc_fcf_record_fcf_index,
					       new_fcf_record));
				/* Choose the new FCF by random selection */
				__lpfc_update_fcf_record(phba, fcf_rec,
							 new_fcf_record,
							 addr_mode, vlan_id, 0);
			}
		}
		spin_unlock_irq(&phba->hbalock);
		goto read_next_fcf;
	}
	/*
	 * This is the first suitable FCF record, choose this record for
	 * initial best-fit FCF.
	 */
	if (fcf_rec) {
		lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
				"2840 Update initial FCF candidate "
				"with FCF (x%x)\n",
				bf_get(lpfc_fcf_record_fcf_index,
				       new_fcf_record));
		__lpfc_update_fcf_record(phba, fcf_rec, new_fcf_record,
					 addr_mode, vlan_id, (boot_flag ?
					 BOOT_ENABLE : 0));
		phba->fcf.fcf_flag |= FCF_AVAILABLE;
		/* Setup initial running random FCF selection count */
		phba->fcf.eligible_fcf_cnt = 1;
		/* Seeding the random number generator for random selection */
		seed = (uint32_t)(0xFFFFFFFF & jiffies);
		srandom32(seed);
	}
	spin_unlock_irq(&phba->hbalock);
	goto read_next_fcf;

read_next_fcf:
	lpfc_sli4_mbox_cmd_free(phba, mboxq);
	if (next_fcf_index == LPFC_FCOE_FCF_NEXT_NONE || next_fcf_index == 0) {
		if (phba->fcf.fcf_flag & FCF_REDISC_FOV) {
			/*
			 * Case of FCF fast failover scan
			 */

			/*
			 * It has not found any suitable FCF record, cancel
			 * FCF scan inprogress, and do nothing
			 */
			if (!(phba->fcf.failover_rec.flag & RECORD_VALID)) {
				lpfc_printf_log(phba, KERN_WARNING, LOG_FIP,
					       "2782 No suitable FCF found: "
					       "(x%x/x%x)\n",
					       phba->fcoe_eventtag_at_fcf_scan,
					       bf_get(lpfc_fcf_record_fcf_index,
						      new_fcf_record));
				spin_lock_irq(&phba->hbalock);
				if (phba->hba_flag & HBA_DEVLOSS_TMO) {
					phba->hba_flag &= ~FCF_TS_INPROG;
					spin_unlock_irq(&phba->hbalock);
					/* Unregister in-use FCF and rescan */
					lpfc_printf_log(phba, KERN_INFO,
							LOG_FIP,
							"2864 On devloss tmo "
							"unreg in-use FCF and "
							"rescan FCF table\n");
					lpfc_unregister_fcf_rescan(phba);
					return;
				}
				/*
				 * Let next new FCF event trigger fast failover
				 */
				phba->hba_flag &= ~FCF_TS_INPROG;
				spin_unlock_irq(&phba->hbalock);
				return;
			}
			/*
			 * It has found a suitable FCF record that is not
			 * the same as in-use FCF record, unregister the
			 * in-use FCF record, replace the in-use FCF record
			 * with the new FCF record, mark FCF fast failover
			 * completed, and then start register the new FCF
			 * record.
			 */

			/* Unregister the current in-use FCF record */
			lpfc_unregister_fcf(phba);

			/* Replace in-use record with the new record */
			lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
					"2842 Replace in-use FCF (x%x) "
					"with failover FCF (x%x)\n",
					phba->fcf.current_rec.fcf_indx,
					phba->fcf.failover_rec.fcf_indx);
			memcpy(&phba->fcf.current_rec,
			       &phba->fcf.failover_rec,
			       sizeof(struct lpfc_fcf_rec));
			/*
			 * Mark the fast FCF failover rediscovery completed
			 * and the start of the first round of the roundrobin
			 * FCF failover.
			 */
			spin_lock_irq(&phba->hbalock);
			phba->fcf.fcf_flag &= ~FCF_REDISC_FOV;
			spin_unlock_irq(&phba->hbalock);
			/* Register to the new FCF record */
			lpfc_register_fcf(phba);
		} else {
			/*
			 * In case of transaction period to fast FCF failover,
			 * do nothing when search to the end of the FCF table.
			 */
			if ((phba->fcf.fcf_flag & FCF_REDISC_EVT) ||
			    (phba->fcf.fcf_flag & FCF_REDISC_PEND))
				return;

			if (phba->cfg_fcf_failover_policy == LPFC_FCF_FOV &&
				phba->fcf.fcf_flag & FCF_IN_USE) {
				/*
				 * In case the current in-use FCF record no
				 * longer existed during FCF discovery that
				 * was not triggered by fast FCF failover
				 * process, treat it as fast FCF failover.
				 */
				lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
						"2841 In-use FCF record (x%x) "
						"not reported, entering fast "
						"FCF failover mode scanning.\n",
						phba->fcf.current_rec.fcf_indx);
				spin_lock_irq(&phba->hbalock);
				phba->fcf.fcf_flag |= FCF_REDISC_FOV;
				spin_unlock_irq(&phba->hbalock);
				lpfc_sli4_fcf_scan_read_fcf_rec(phba,
						LPFC_FCOE_FCF_GET_FIRST);
				return;
			}
			/* Register to the new FCF record */
			lpfc_register_fcf(phba);
		}
	} else
		lpfc_sli4_fcf_scan_read_fcf_rec(phba, next_fcf_index);
	return;

out:
	lpfc_sli4_mbox_cmd_free(phba, mboxq);
	lpfc_register_fcf(phba);

	return;
}