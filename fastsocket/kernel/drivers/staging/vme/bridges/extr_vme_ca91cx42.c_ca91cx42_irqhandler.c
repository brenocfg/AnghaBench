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
typedef  int u32 ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {void* base; } ;

/* Variables and functions */
 int CA91CX42_LINT_DMA ; 
 int CA91CX42_LINT_LERR ; 
 int CA91CX42_LINT_LM0 ; 
 int CA91CX42_LINT_LM1 ; 
 int CA91CX42_LINT_LM2 ; 
 int CA91CX42_LINT_LM3 ; 
 int CA91CX42_LINT_MBOX ; 
 int CA91CX42_LINT_SW_IACK ; 
 int CA91CX42_LINT_VERR ; 
 int CA91CX42_LINT_VIRQ1 ; 
 int CA91CX42_LINT_VIRQ2 ; 
 int CA91CX42_LINT_VIRQ3 ; 
 int CA91CX42_LINT_VIRQ4 ; 
 int CA91CX42_LINT_VIRQ5 ; 
 int CA91CX42_LINT_VIRQ6 ; 
 int CA91CX42_LINT_VIRQ7 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int LINT_EN ; 
 int LINT_STAT ; 
 int ca91cx42_DMA_irqhandler () ; 
 int ca91cx42_IACK_irqhandler () ; 
 int ca91cx42_LERR_irqhandler () ; 
 int ca91cx42_LM_irqhandler (int) ; 
 int ca91cx42_MB_irqhandler (int) ; 
 int ca91cx42_VERR_irqhandler () ; 
 int ca91cx42_VIRQ_irqhandler (int) ; 
 TYPE_1__* ca91cx42_bridge ; 
 int ioread32 (void*) ; 
 int /*<<< orphan*/  iowrite32 (int,void*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t ca91cx42_irqhandler(int irq, void *dev_id)
{
	u32 stat, enable, serviced = 0;

	if (dev_id != ca91cx42_bridge->base)
		return IRQ_NONE;

	enable = ioread32(ca91cx42_bridge->base + LINT_EN);
	stat = ioread32(ca91cx42_bridge->base + LINT_STAT);

	/* Only look at unmasked interrupts */
	stat &= enable;

	if (unlikely(!stat))
		return IRQ_NONE;

	if (stat & CA91CX42_LINT_DMA)
		serviced |= ca91cx42_DMA_irqhandler();
	if (stat & (CA91CX42_LINT_LM0 | CA91CX42_LINT_LM1 | CA91CX42_LINT_LM2 |
			CA91CX42_LINT_LM3))
		serviced |= ca91cx42_LM_irqhandler(stat);
	if (stat & CA91CX42_LINT_MBOX)
		serviced |= ca91cx42_MB_irqhandler(stat);
	if (stat & CA91CX42_LINT_SW_IACK)
		serviced |= ca91cx42_IACK_irqhandler();
	if (stat & CA91CX42_LINT_VERR)
		serviced |= ca91cx42_VERR_irqhandler();
	if (stat & CA91CX42_LINT_LERR)
		serviced |= ca91cx42_LERR_irqhandler();
	if (stat & (CA91CX42_LINT_VIRQ1 | CA91CX42_LINT_VIRQ2 |
			CA91CX42_LINT_VIRQ3 | CA91CX42_LINT_VIRQ4 |
			CA91CX42_LINT_VIRQ5 | CA91CX42_LINT_VIRQ6 |
			CA91CX42_LINT_VIRQ7))
		serviced |= ca91cx42_VIRQ_irqhandler(stat);

	/* Clear serviced interrupts */
	iowrite32(stat, ca91cx42_bridge->base + LINT_STAT);

	return IRQ_HANDLED;
}