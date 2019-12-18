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
struct uic {int /*<<< orphan*/  lock; scalar_t__ dcrbase; } ;
struct irq_desc {unsigned int status; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IRQ_LEVEL ; 
#define  IRQ_TYPE_EDGE_FALLING 132 
#define  IRQ_TYPE_EDGE_RISING 131 
#define  IRQ_TYPE_LEVEL_HIGH 130 
#define  IRQ_TYPE_LEVEL_LOW 129 
#define  IRQ_TYPE_NONE 128 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 scalar_t__ UIC_PR ; 
 scalar_t__ UIC_TR ; 
 struct uic* get_irq_chip_data (unsigned int) ; 
 struct irq_desc* get_irq_desc (unsigned int) ; 
 int mfdcr (scalar_t__) ; 
 int /*<<< orphan*/  mtdcr (scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int uic_irq_to_hw (unsigned int) ; 
 int /*<<< orphan*/  uic_mask_irq (unsigned int) ; 

__attribute__((used)) static int uic_set_irq_type(unsigned int virq, unsigned int flow_type)
{
	struct uic *uic = get_irq_chip_data(virq);
	unsigned int src = uic_irq_to_hw(virq);
	struct irq_desc *desc = get_irq_desc(virq);
	unsigned long flags;
	int trigger, polarity;
	u32 tr, pr, mask;

	switch (flow_type & IRQ_TYPE_SENSE_MASK) {
	case IRQ_TYPE_NONE:
		uic_mask_irq(virq);
		return 0;

	case IRQ_TYPE_EDGE_RISING:
		trigger = 1; polarity = 1;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		trigger = 1; polarity = 0;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		trigger = 0; polarity = 1;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		trigger = 0; polarity = 0;
		break;
	default:
		return -EINVAL;
	}

	mask = ~(1 << (31 - src));

	spin_lock_irqsave(&uic->lock, flags);
	tr = mfdcr(uic->dcrbase + UIC_TR);
	pr = mfdcr(uic->dcrbase + UIC_PR);
	tr = (tr & mask) | (trigger << (31-src));
	pr = (pr & mask) | (polarity << (31-src));

	mtdcr(uic->dcrbase + UIC_PR, pr);
	mtdcr(uic->dcrbase + UIC_TR, tr);

	desc->status &= ~(IRQ_TYPE_SENSE_MASK | IRQ_LEVEL);
	desc->status |= flow_type & IRQ_TYPE_SENSE_MASK;
	if (!trigger)
		desc->status |= IRQ_LEVEL;

	spin_unlock_irqrestore(&uic->lock, flags);

	return 0;
}