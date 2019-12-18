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
 unsigned int BIT_MASK (unsigned int) ; 
 unsigned int BIT_WORD (unsigned int) ; 
 int /*<<< orphan*/  CP_INTC_SYS_POLARITY (unsigned int) ; 
 int /*<<< orphan*/  CP_INTC_SYS_TYPE (unsigned int) ; 
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 unsigned int cp_intc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_intc_write (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cp_intc_set_irq_type(unsigned int irq, unsigned int flow_type)
{
	unsigned reg		= BIT_WORD(irq);
	unsigned mask		= BIT_MASK(irq);
	unsigned polarity	= cp_intc_read(CP_INTC_SYS_POLARITY(reg));
	unsigned type		= cp_intc_read(CP_INTC_SYS_TYPE(reg));

	switch (flow_type) {
	case IRQ_TYPE_EDGE_RISING:
		polarity |= mask;
		type |= mask;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		polarity &= ~mask;
		type |= mask;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		polarity |= mask;
		type &= ~mask;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		polarity &= ~mask;
		type &= ~mask;
		break;
	default:
		return -EINVAL;
	}

	cp_intc_write(polarity, CP_INTC_SYS_POLARITY(reg));
	cp_intc_write(type, CP_INTC_SYS_TYPE(reg));

	return 0;
}