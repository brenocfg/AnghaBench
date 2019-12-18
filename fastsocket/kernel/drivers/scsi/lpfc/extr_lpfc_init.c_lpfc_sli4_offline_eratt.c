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
struct lpfc_hba {int /*<<< orphan*/  link_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPFC_HBA_ERROR ; 
 int /*<<< orphan*/  LPFC_MBX_NO_WAIT ; 
 int /*<<< orphan*/  lpfc_hba_down_post (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_offline (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_offline_prep (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli4_brdreset (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_post_status_check (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_unblock_mgmt_io (struct lpfc_hba*) ; 

void
lpfc_sli4_offline_eratt(struct lpfc_hba *phba)
{
	lpfc_offline_prep(phba, LPFC_MBX_NO_WAIT);
	lpfc_offline(phba);
	lpfc_sli4_brdreset(phba);
	lpfc_hba_down_post(phba);
	lpfc_sli4_post_status_check(phba);
	lpfc_unblock_mgmt_io(phba);
	phba->link_state = LPFC_HBA_ERROR;
}