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
struct lpfc_hba {int /*<<< orphan*/  hbalock; } ;
struct lpfc_cq_event {int dummy; } ;

/* Variables and functions */
 struct lpfc_cq_event* __lpfc_sli4_cq_event_alloc (struct lpfc_hba*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct lpfc_cq_event *
lpfc_sli4_cq_event_alloc(struct lpfc_hba *phba)
{
	struct lpfc_cq_event *cq_event;
	unsigned long iflags;

	spin_lock_irqsave(&phba->hbalock, iflags);
	cq_event = __lpfc_sli4_cq_event_alloc(phba);
	spin_unlock_irqrestore(&phba->hbalock, iflags);
	return cq_event;
}