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
struct lpfc_hba {int /*<<< orphan*/  bit_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FABRIC_COMANDS_BLOCKED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_resume_fabric_iocbs (struct lpfc_hba*) ; 

void
lpfc_unblock_fabric_iocbs(struct lpfc_hba *phba)
{
	clear_bit(FABRIC_COMANDS_BLOCKED, &phba->bit_flags);

	lpfc_resume_fabric_iocbs(phba);
	return;
}