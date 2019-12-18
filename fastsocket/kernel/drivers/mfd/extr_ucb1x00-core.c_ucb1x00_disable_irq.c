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
struct ucb1x00 {int irq_ris_enbl; int irq_fal_enbl; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int UCB_FALLING ; 
 int /*<<< orphan*/  UCB_IE_FAL ; 
 int /*<<< orphan*/  UCB_IE_RIS ; 
 int UCB_RISING ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ucb1x00_disable (struct ucb1x00*) ; 
 int /*<<< orphan*/  ucb1x00_enable (struct ucb1x00*) ; 
 int /*<<< orphan*/  ucb1x00_reg_write (struct ucb1x00*,int /*<<< orphan*/ ,int) ; 

void ucb1x00_disable_irq(struct ucb1x00 *ucb, unsigned int idx, int edges)
{
	unsigned long flags;

	if (idx < 16) {
		spin_lock_irqsave(&ucb->lock, flags);

		ucb1x00_enable(ucb);
		if (edges & UCB_RISING) {
			ucb->irq_ris_enbl &= ~(1 << idx);
			ucb1x00_reg_write(ucb, UCB_IE_RIS, ucb->irq_ris_enbl);
		}
		if (edges & UCB_FALLING) {
			ucb->irq_fal_enbl &= ~(1 << idx);
			ucb1x00_reg_write(ucb, UCB_IE_FAL, ucb->irq_fal_enbl);
		}
		ucb1x00_disable(ucb);
		spin_unlock_irqrestore(&ucb->lock, flags);
	}
}