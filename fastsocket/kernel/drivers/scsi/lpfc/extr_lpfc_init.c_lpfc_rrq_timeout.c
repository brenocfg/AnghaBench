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
struct lpfc_hba {TYPE_1__* pport; int /*<<< orphan*/  hba_flag; } ;
struct TYPE_2__ {int /*<<< orphan*/  work_port_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  HBA_RRQ_ACTIVE ; 
 int /*<<< orphan*/  lpfc_worker_wake_up (struct lpfc_hba*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
lpfc_rrq_timeout(unsigned long ptr)
{
	struct lpfc_hba *phba;
	unsigned long iflag;

	phba = (struct lpfc_hba *)ptr;
	spin_lock_irqsave(&phba->pport->work_port_lock, iflag);
	phba->hba_flag |= HBA_RRQ_ACTIVE;
	spin_unlock_irqrestore(&phba->pport->work_port_lock, iflag);
	lpfc_worker_wake_up(phba);
}