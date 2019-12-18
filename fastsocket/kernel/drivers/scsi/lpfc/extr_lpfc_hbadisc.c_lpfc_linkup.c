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
struct lpfc_vport {int dummy; } ;
struct lpfc_hba {int max_vports; int /*<<< orphan*/  fabric_block_timer; int /*<<< orphan*/  bit_flags; int /*<<< orphan*/  link_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  FABRIC_COMANDS_BLOCKED ; 
 int /*<<< orphan*/  LPFC_LINK_UP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_cleanup_wt_rrqs (struct lpfc_hba*) ; 
 struct lpfc_vport** lpfc_create_vport_work_array (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_destroy_vport_work_array (struct lpfc_hba*,struct lpfc_vport**) ; 
 int /*<<< orphan*/  lpfc_linkup_port (struct lpfc_vport*) ; 

__attribute__((used)) static int
lpfc_linkup(struct lpfc_hba *phba)
{
	struct lpfc_vport **vports;
	int i;

	lpfc_cleanup_wt_rrqs(phba);
	phba->link_state = LPFC_LINK_UP;

	/* Unblock fabric iocbs if they are blocked */
	clear_bit(FABRIC_COMANDS_BLOCKED, &phba->bit_flags);
	del_timer_sync(&phba->fabric_block_timer);

	vports = lpfc_create_vport_work_array(phba);
	if (vports != NULL)
		for (i = 0; i <= phba->max_vports && vports[i] != NULL; i++)
			lpfc_linkup_port(vports[i]);
	lpfc_destroy_vport_work_array(phba, vports);

	return 0;
}