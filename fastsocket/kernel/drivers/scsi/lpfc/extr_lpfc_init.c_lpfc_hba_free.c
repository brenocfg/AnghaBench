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
struct TYPE_2__ {struct lpfc_hba* ring; } ;
struct lpfc_hba {TYPE_1__ sli; int /*<<< orphan*/  brd_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_hba_index ; 

__attribute__((used)) static void
lpfc_hba_free(struct lpfc_hba *phba)
{
	/* Release the driver assigned board number */
	idr_remove(&lpfc_hba_index, phba->brd_no);

	/* Free memory allocated with sli rings */
	kfree(phba->sli.ring);
	phba->sli.ring = NULL;

	kfree(phba);
	return;
}