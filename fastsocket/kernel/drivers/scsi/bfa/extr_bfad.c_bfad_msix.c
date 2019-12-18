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
struct list_head {int dummy; } ;
struct bfad_s {int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfa; } ;
struct TYPE_2__ {int /*<<< orphan*/  entry; } ;
struct bfad_msix_s {TYPE_1__ msix; struct bfad_s* bfad; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  bfa_comp_deq (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  bfa_comp_free (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  bfa_comp_process (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  bfa_msix (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t
bfad_msix(int irq, void *dev_id)
{
	struct bfad_msix_s *vec = dev_id;
	struct bfad_s *bfad = vec->bfad;
	struct list_head doneq;
	unsigned long   flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);

	bfa_msix(&bfad->bfa, vec->msix.entry);
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