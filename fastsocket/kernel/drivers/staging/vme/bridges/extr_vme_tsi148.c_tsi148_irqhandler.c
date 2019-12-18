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
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ TSI148_LCSR_INTC ; 
 scalar_t__ TSI148_LCSR_INTEO ; 
 scalar_t__ TSI148_LCSR_INTS ; 
 int TSI148_LCSR_INTS_DMA0S ; 
 int TSI148_LCSR_INTS_DMA1S ; 
 int TSI148_LCSR_INTS_IACKS ; 
 int TSI148_LCSR_INTS_IRQ1S ; 
 int TSI148_LCSR_INTS_IRQ2S ; 
 int TSI148_LCSR_INTS_IRQ3S ; 
 int TSI148_LCSR_INTS_IRQ4S ; 
 int TSI148_LCSR_INTS_IRQ5S ; 
 int TSI148_LCSR_INTS_IRQ6S ; 
 int TSI148_LCSR_INTS_IRQ7S ; 
 int TSI148_LCSR_INTS_LM0S ; 
 int TSI148_LCSR_INTS_LM1S ; 
 int TSI148_LCSR_INTS_LM2S ; 
 int TSI148_LCSR_INTS_LM3S ; 
 int TSI148_LCSR_INTS_MB0S ; 
 int TSI148_LCSR_INTS_MB1S ; 
 int TSI148_LCSR_INTS_MB2S ; 
 int TSI148_LCSR_INTS_MB3S ; 
 int TSI148_LCSR_INTS_PERRS ; 
 int TSI148_LCSR_INTS_VERRS ; 
 int ioread32be (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32be (int,scalar_t__) ; 
 int tsi148_DMA_irqhandler (int) ; 
 int tsi148_IACK_irqhandler () ; 
 int tsi148_LM_irqhandler (int) ; 
 int tsi148_MB_irqhandler (int) ; 
 int tsi148_PERR_irqhandler () ; 
 int tsi148_VERR_irqhandler () ; 
 int tsi148_VIRQ_irqhandler (int) ; 
 TYPE_1__* tsi148_bridge ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t tsi148_irqhandler(int irq, void *dev_id)
{
	u32 stat, enable, serviced = 0;

	/* Determine which interrupts are unmasked and set */
	enable = ioread32be(tsi148_bridge->base + TSI148_LCSR_INTEO);
	stat = ioread32be(tsi148_bridge->base + TSI148_LCSR_INTS);

	/* Only look at unmasked interrupts */
	stat &= enable;

	if (unlikely(!stat)) {
		return IRQ_NONE;
	}

	/* Call subhandlers as appropriate */
	/* DMA irqs */
	if (stat & (TSI148_LCSR_INTS_DMA1S | TSI148_LCSR_INTS_DMA0S))
		serviced |= tsi148_DMA_irqhandler(stat);

	/* Location monitor irqs */
	if (stat & (TSI148_LCSR_INTS_LM3S | TSI148_LCSR_INTS_LM2S |
			TSI148_LCSR_INTS_LM1S | TSI148_LCSR_INTS_LM0S))
		serviced |= tsi148_LM_irqhandler(stat);

	/* Mail box irqs */
	if (stat & (TSI148_LCSR_INTS_MB3S | TSI148_LCSR_INTS_MB2S |
			TSI148_LCSR_INTS_MB1S | TSI148_LCSR_INTS_MB0S))
		serviced |= tsi148_MB_irqhandler(stat);

	/* PCI bus error */
	if (stat & TSI148_LCSR_INTS_PERRS)
		serviced |= tsi148_PERR_irqhandler();

	/* VME bus error */
	if (stat & TSI148_LCSR_INTS_VERRS)
		serviced |= tsi148_VERR_irqhandler();

	/* IACK irq */
	if (stat & TSI148_LCSR_INTS_IACKS)
		serviced |= tsi148_IACK_irqhandler();

	/* VME bus irqs */
	if (stat & (TSI148_LCSR_INTS_IRQ7S | TSI148_LCSR_INTS_IRQ6S |
			TSI148_LCSR_INTS_IRQ5S | TSI148_LCSR_INTS_IRQ4S |
			TSI148_LCSR_INTS_IRQ3S | TSI148_LCSR_INTS_IRQ2S |
			TSI148_LCSR_INTS_IRQ1S))
		serviced |= tsi148_VIRQ_irqhandler(stat);

	/* Clear serviced interrupts */
	iowrite32be(serviced, tsi148_bridge->base + TSI148_LCSR_INTC);

	return IRQ_HANDLED;
}