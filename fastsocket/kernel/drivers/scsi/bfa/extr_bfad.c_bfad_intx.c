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
struct list_head {int dummy; } ;
struct bfad_s {int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfa; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  bfa_comp_deq (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  bfa_comp_free (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  bfa_comp_process (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  bfa_intx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

irqreturn_t
bfad_intx(int irq, void *dev_id)
{
	struct bfad_s	*bfad = dev_id;
	struct list_head	doneq;
	unsigned long	flags;
	bfa_boolean_t rc;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	rc = bfa_intx(&bfad->bfa);
	if (!rc) {
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		return IRQ_NONE;
	}

	bfa_comp_deq(&bfad->bfa, &doneq);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	if (!list_empty(&doneq)) {
		bfa_comp_process(&bfad->bfa, &doneq);

		spin_lock_irqsave(&bfad->bfad_lock, flags);
		bfa_comp_free(&bfad->bfa, &doneq);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	}

	return IRQ_HANDLED;

}