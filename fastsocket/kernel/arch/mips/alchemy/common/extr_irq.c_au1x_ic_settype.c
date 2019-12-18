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
struct irq_chip {int dummy; } ;

/* Variables and functions */
 unsigned int AU1000_INTC0_INT_BASE ; 
 unsigned int AU1000_INTC1_INT_BASE ; 
 int EINVAL ; 
 unsigned long IC0_CFG0CLR ; 
 unsigned long IC0_CFG0SET ; 
 unsigned long IC0_CFG1CLR ; 
 unsigned long IC0_CFG1SET ; 
 unsigned long IC0_CFG2CLR ; 
 unsigned long IC0_CFG2SET ; 
 unsigned long IC1_CFG0CLR ; 
 unsigned long IC1_CFG0SET ; 
 unsigned long IC1_CFG1CLR ; 
 unsigned long IC1_CFG1SET ; 
 unsigned long IC1_CFG2CLR ; 
 unsigned long IC1_CFG2SET ; 
#define  IRQ_TYPE_EDGE_BOTH 133 
#define  IRQ_TYPE_EDGE_FALLING 132 
#define  IRQ_TYPE_EDGE_RISING 131 
#define  IRQ_TYPE_LEVEL_HIGH 130 
#define  IRQ_TYPE_LEVEL_LOW 129 
#define  IRQ_TYPE_NONE 128 
 struct irq_chip au1x_ic0_chip ; 
 struct irq_chip au1x_ic1_chip ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_writel (int,unsigned long) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  set_irq_chip (unsigned int,struct irq_chip*) ; 
 int /*<<< orphan*/  set_irq_chip_and_handler_name (unsigned int,struct irq_chip*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int au1x_ic_settype(unsigned int irq, unsigned int flow_type)
{
	struct irq_chip *chip;
	unsigned long icr[6];
	unsigned int bit, ic;
	int ret;

	if (irq >= AU1000_INTC1_INT_BASE) {
		bit = irq - AU1000_INTC1_INT_BASE;
		chip = &au1x_ic1_chip;
		ic = 1;
	} else {
		bit = irq - AU1000_INTC0_INT_BASE;
		chip = &au1x_ic0_chip;
		ic = 0;
	}

	if (bit > 31)
		return -EINVAL;

	icr[0] = ic ? IC1_CFG0SET : IC0_CFG0SET;
	icr[1] = ic ? IC1_CFG1SET : IC0_CFG1SET;
	icr[2] = ic ? IC1_CFG2SET : IC0_CFG2SET;
	icr[3] = ic ? IC1_CFG0CLR : IC0_CFG0CLR;
	icr[4] = ic ? IC1_CFG1CLR : IC0_CFG1CLR;
	icr[5] = ic ? IC1_CFG2CLR : IC0_CFG2CLR;

	ret = 0;

	switch (flow_type) {	/* cfgregs 2:1:0 */
	case IRQ_TYPE_EDGE_RISING:	/* 0:0:1 */
		au_writel(1 << bit, icr[5]);
		au_writel(1 << bit, icr[4]);
		au_writel(1 << bit, icr[0]);
		set_irq_chip_and_handler_name(irq, chip,
				handle_edge_irq, "riseedge");
		break;
	case IRQ_TYPE_EDGE_FALLING:	/* 0:1:0 */
		au_writel(1 << bit, icr[5]);
		au_writel(1 << bit, icr[1]);
		au_writel(1 << bit, icr[3]);
		set_irq_chip_and_handler_name(irq, chip,
				handle_edge_irq, "falledge");
		break;
	case IRQ_TYPE_EDGE_BOTH:	/* 0:1:1 */
		au_writel(1 << bit, icr[5]);
		au_writel(1 << bit, icr[1]);
		au_writel(1 << bit, icr[0]);
		set_irq_chip_and_handler_name(irq, chip,
				handle_edge_irq, "bothedge");
		break;
	case IRQ_TYPE_LEVEL_HIGH:	/* 1:0:1 */
		au_writel(1 << bit, icr[2]);
		au_writel(1 << bit, icr[4]);
		au_writel(1 << bit, icr[0]);
		set_irq_chip_and_handler_name(irq, chip,
				handle_level_irq, "hilevel");
		break;
	case IRQ_TYPE_LEVEL_LOW:	/* 1:1:0 */
		au_writel(1 << bit, icr[2]);
		au_writel(1 << bit, icr[1]);
		au_writel(1 << bit, icr[3]);
		set_irq_chip_and_handler_name(irq, chip,
				handle_level_irq, "lowlevel");
		break;
	case IRQ_TYPE_NONE:		/* 0:0:0 */
		au_writel(1 << bit, icr[5]);
		au_writel(1 << bit, icr[4]);
		au_writel(1 << bit, icr[3]);
		/* set at least chip so we can call set_irq_type() on it */
		set_irq_chip(irq, chip);
		break;
	default:
		ret = -EINVAL;
	}
	au_sync();

	return ret;
}