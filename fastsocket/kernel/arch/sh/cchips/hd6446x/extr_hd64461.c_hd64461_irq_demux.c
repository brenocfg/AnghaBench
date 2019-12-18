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
struct irq_desc {int dummy; } ;

/* Variables and functions */
 unsigned int HD64461_IRQBASE ; 
 int HD64461_IRQ_NUM ; 
 int /*<<< orphan*/  HD64461_NIRR ; 
 unsigned short ctrl_inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_level_irq (unsigned int,struct irq_desc*) ; 
 struct irq_desc* irq_desc ; 

__attribute__((used)) static void hd64461_irq_demux(unsigned int irq, struct irq_desc *desc)
{
	unsigned short intv = ctrl_inw(HD64461_NIRR);
	struct irq_desc *ext_desc;
	unsigned int ext_irq = HD64461_IRQBASE;

	intv &= (1 << HD64461_IRQ_NUM) - 1;

	while (intv) {
		if (intv & 1) {
			ext_desc = irq_desc + ext_irq;
			handle_level_irq(ext_irq, ext_desc);
		}
		intv >>= 1;
		ext_irq++;
	}
}