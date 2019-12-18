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
struct sih_agent {unsigned int irq_base; int imr_change_pending; int /*<<< orphan*/  mask_work; int /*<<< orphan*/  imr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 struct sih_agent* get_irq_chip_data (unsigned int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sih_agent_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wq ; 

__attribute__((used)) static void twl4030_sih_mask(unsigned irq)
{
	struct sih_agent *sih = get_irq_chip_data(irq);
	unsigned long flags;

	spin_lock_irqsave(&sih_agent_lock, flags);
	sih->imr |= BIT(irq - sih->irq_base);
	sih->imr_change_pending = true;
	queue_work(wq, &sih->mask_work);
	spin_unlock_irqrestore(&sih_agent_lock, flags);
}