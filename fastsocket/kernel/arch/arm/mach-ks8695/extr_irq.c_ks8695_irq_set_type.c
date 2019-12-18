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

/* Variables and functions */
 int EINVAL ; 
 unsigned long IOPC_IOEINT0TM ; 
 unsigned long IOPC_IOEINT0_MODE (unsigned long) ; 
 unsigned long IOPC_IOEINT1TM ; 
 unsigned long IOPC_IOEINT1_MODE (unsigned long) ; 
 unsigned long IOPC_IOEINT2TM ; 
 unsigned long IOPC_IOEINT2_MODE (unsigned long) ; 
 unsigned long IOPC_IOEINT3TM ; 
 unsigned long IOPC_IOEINT3_MODE (unsigned long) ; 
 unsigned long IOPC_TM_EDGE ; 
 unsigned long IOPC_TM_FALLING ; 
 unsigned long IOPC_TM_HIGH ; 
 unsigned long IOPC_TM_LOW ; 
 unsigned long IOPC_TM_RISING ; 
#define  IRQ_TYPE_EDGE_BOTH 136 
#define  IRQ_TYPE_EDGE_FALLING 135 
#define  IRQ_TYPE_EDGE_RISING 134 
#define  IRQ_TYPE_LEVEL_HIGH 133 
#define  IRQ_TYPE_LEVEL_LOW 132 
 scalar_t__ KS8695_GPIO_VA ; 
 scalar_t__ KS8695_IOPC ; 
#define  KS8695_IRQ_EXTERN0 131 
#define  KS8695_IRQ_EXTERN1 130 
#define  KS8695_IRQ_EXTERN2 129 
#define  KS8695_IRQ_EXTERN3 128 
 unsigned long __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  ks8695_irq_edge_chip ; 
 int /*<<< orphan*/  ks8695_irq_level_chip ; 
 int /*<<< orphan*/  set_irq_chip (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_irq_handler (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ks8695_irq_set_type(unsigned int irqno, unsigned int type)
{
	unsigned long ctrl, mode;
	unsigned short level_triggered = 0;

	ctrl = __raw_readl(KS8695_GPIO_VA + KS8695_IOPC);

	switch (type) {
		case IRQ_TYPE_LEVEL_HIGH:
			mode = IOPC_TM_HIGH;
			level_triggered = 1;
			break;
		case IRQ_TYPE_LEVEL_LOW:
			mode = IOPC_TM_LOW;
			level_triggered = 1;
			break;
		case IRQ_TYPE_EDGE_RISING:
			mode = IOPC_TM_RISING;
			break;
		case IRQ_TYPE_EDGE_FALLING:
			mode = IOPC_TM_FALLING;
			break;
		case IRQ_TYPE_EDGE_BOTH:
			mode = IOPC_TM_EDGE;
			break;
		default:
			return -EINVAL;
	}

	switch (irqno) {
		case KS8695_IRQ_EXTERN0:
			ctrl &= ~IOPC_IOEINT0TM;
			ctrl |= IOPC_IOEINT0_MODE(mode);
			break;
		case KS8695_IRQ_EXTERN1:
			ctrl &= ~IOPC_IOEINT1TM;
			ctrl |= IOPC_IOEINT1_MODE(mode);
			break;
		case KS8695_IRQ_EXTERN2:
			ctrl &= ~IOPC_IOEINT2TM;
			ctrl |= IOPC_IOEINT2_MODE(mode);
			break;
		case KS8695_IRQ_EXTERN3:
			ctrl &= ~IOPC_IOEINT3TM;
			ctrl |= IOPC_IOEINT3_MODE(mode);
			break;
		default:
			return -EINVAL;
	}

	if (level_triggered) {
		set_irq_chip(irqno, &ks8695_irq_level_chip);
		set_irq_handler(irqno, handle_level_irq);
	}
	else {
		set_irq_chip(irqno, &ks8695_irq_edge_chip);
		set_irq_handler(irqno, handle_edge_irq);
	}

	__raw_writel(ctrl, KS8695_GPIO_VA + KS8695_IOPC);
	return 0;
}