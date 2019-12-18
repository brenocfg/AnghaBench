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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int fcf_flag; } ;
struct lpfc_hba {scalar_t__ link_state; TYPE_1__ fcf; } ;
struct fcf_record {int dummy; } ;
typedef  int /*<<< orphan*/  LPFC_MBOXQ_t ;

/* Variables and functions */
 int FCF_DISCOVERY ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_FIP ; 
 scalar_t__ LPFC_LINK_UP ; 
 int /*<<< orphan*/  bf_get (int /*<<< orphan*/ ,struct fcf_record*) ; 
 int /*<<< orphan*/  lpfc_fcf_record_fcf_index ; 
 int lpfc_match_fcf_conn_list (struct lpfc_hba*,struct fcf_record*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int lpfc_sli4_fcf_pri_list_add (struct lpfc_hba*,int /*<<< orphan*/ ,struct fcf_record*) ; 
 struct fcf_record* lpfc_sli4_fcf_rec_mbox_parse (struct lpfc_hba*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_sli4_log_fcf_record_info (struct lpfc_hba*,struct fcf_record*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli4_mbox_cmd_free (struct lpfc_hba*,int /*<<< orphan*/ *) ; 

void
lpfc_mbx_cmpl_read_fcf_rec(struct lpfc_hba *phba, LPFC_MBOXQ_t *mboxq)
{
	struct fcf_record *new_fcf_record;
	uint32_t boot_flag, addr_mode;
	uint16_t fcf_index, next_fcf_index;
	uint16_t vlan_id;
	int rc;

	/* If link state is not up, no need to proceed */
	if (phba->link_state < LPFC_LINK_UP)
		goto out;

	/* If FCF discovery period is over, no need to proceed */
	if (!(phba->fcf.fcf_flag & FCF_DISCOVERY))
		goto out;

	/* Parse the FCF record from the non-embedded mailbox command */
	new_fcf_record = lpfc_sli4_fcf_rec_mbox_parse(phba, mboxq,
						      &next_fcf_index);
	if (!new_fcf_record) {
		lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
				"2767 Mailbox command READ_FCF_RECORD "
				"failed to retrieve a FCF record.\n");
		goto out;
	}

	/* Check the connection list for eligibility */
	rc = lpfc_match_fcf_conn_list(phba, new_fcf_record, &boot_flag,
				      &addr_mode, &vlan_id);

	/* Log the FCF record information if turned on */
	lpfc_sli4_log_fcf_record_info(phba, new_fcf_record, vlan_id,
				      next_fcf_index);

	if (!rc)
		goto out;

	/* Update the eligible FCF record index bmask */
	fcf_index = bf_get(lpfc_fcf_record_fcf_index, new_fcf_record);

	rc = lpfc_sli4_fcf_pri_list_add(phba, fcf_index, new_fcf_record);

out:
	lpfc_sli4_mbox_cmd_free(phba, mboxq);
}