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
struct bnad {int /*<<< orphan*/  bna_lock; } ;

/* Variables and functions */
 int BNAD_GET_MBOX_IRQ (struct bnad*) ; 
 int /*<<< orphan*/  bnad_disable_mbox_irq (struct bnad*) ; 
 int /*<<< orphan*/  free_irq (int,struct bnad*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
bnad_mbox_irq_free(struct bnad *bnad)
{
	int irq;
	unsigned long flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bnad_disable_mbox_irq(bnad);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	irq = BNAD_GET_MBOX_IRQ(bnad);
	free_irq(irq, bnad);
}