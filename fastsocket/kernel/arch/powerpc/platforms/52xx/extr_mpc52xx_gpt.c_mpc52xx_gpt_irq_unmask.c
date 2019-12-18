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
struct mpc52xx_gpt_priv {int /*<<< orphan*/  lock; TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPC52xx_GPT_MODE_IRQ_EN ; 
 struct mpc52xx_gpt_priv* get_irq_chip_data (unsigned int) ; 
 int /*<<< orphan*/  setbits32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mpc52xx_gpt_irq_unmask(unsigned int virq)
{
	struct mpc52xx_gpt_priv *gpt = get_irq_chip_data(virq);
	unsigned long flags;

	spin_lock_irqsave(&gpt->lock, flags);
	setbits32(&gpt->regs->mode, MPC52xx_GPT_MODE_IRQ_EN);
	spin_unlock_irqrestore(&gpt->lock, flags);
}