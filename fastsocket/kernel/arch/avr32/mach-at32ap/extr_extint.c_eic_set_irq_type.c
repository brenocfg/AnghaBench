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
typedef  int u32 ;
struct irq_desc {unsigned int status; } ;
struct eic {unsigned int first_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDGE ; 
 int EINVAL ; 
 unsigned int IRQ_LEVEL ; 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 unsigned int IRQ_TYPE_NONE ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 int /*<<< orphan*/  LEVEL ; 
 int /*<<< orphan*/  MODE ; 
 int /*<<< orphan*/  __set_irq_handler_unlocked (unsigned int,int /*<<< orphan*/ ) ; 
 int eic_readl (struct eic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eic_writel (struct eic*,int /*<<< orphan*/ ,int) ; 
 struct eic* get_irq_chip_data (unsigned int) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 struct irq_desc* irq_desc ; 

__attribute__((used)) static int eic_set_irq_type(unsigned int irq, unsigned int flow_type)
{
	struct eic *eic = get_irq_chip_data(irq);
	struct irq_desc *desc;
	unsigned int i = irq - eic->first_irq;
	u32 mode, edge, level;
	int ret = 0;

	flow_type &= IRQ_TYPE_SENSE_MASK;
	if (flow_type == IRQ_TYPE_NONE)
		flow_type = IRQ_TYPE_LEVEL_LOW;

	desc = &irq_desc[irq];

	mode = eic_readl(eic, MODE);
	edge = eic_readl(eic, EDGE);
	level = eic_readl(eic, LEVEL);

	switch (flow_type) {
	case IRQ_TYPE_LEVEL_LOW:
		mode |= 1 << i;
		level &= ~(1 << i);
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		mode |= 1 << i;
		level |= 1 << i;
		break;
	case IRQ_TYPE_EDGE_RISING:
		mode &= ~(1 << i);
		edge |= 1 << i;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		mode &= ~(1 << i);
		edge &= ~(1 << i);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	if (ret == 0) {
		eic_writel(eic, MODE, mode);
		eic_writel(eic, EDGE, edge);
		eic_writel(eic, LEVEL, level);

		if (flow_type & (IRQ_TYPE_LEVEL_LOW | IRQ_TYPE_LEVEL_HIGH)) {
			flow_type |= IRQ_LEVEL;
			__set_irq_handler_unlocked(irq, handle_level_irq);
		} else
			__set_irq_handler_unlocked(irq, handle_edge_irq);
		desc->status &= ~(IRQ_TYPE_SENSE_MASK | IRQ_LEVEL);
		desc->status |= flow_type;
	}

	return ret;
}