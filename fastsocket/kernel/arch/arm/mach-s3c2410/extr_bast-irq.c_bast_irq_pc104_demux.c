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
struct irq_desc {TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ack ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BAST_VA_PC104_IRQREQ ; 
 int IRQ_ISA ; 
 int __raw_readb (int /*<<< orphan*/ ) ; 
 unsigned int* bast_pc104_irqs ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 struct irq_desc* irq_desc ; 
 int /*<<< orphan*/  stub1 (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
bast_irq_pc104_demux(unsigned int irq,
		     struct irq_desc *desc)
{
	unsigned int stat;
	unsigned int irqno;
	int i;

	stat = __raw_readb(BAST_VA_PC104_IRQREQ) & 0xf;

	if (unlikely(stat == 0)) {
		/* ack if we get an irq with nothing (ie, startup) */

		desc = irq_desc + IRQ_ISA;
		desc->chip->ack(IRQ_ISA);
	} else {
		/* handle the IRQ */

		for (i = 0; stat != 0; i++, stat >>= 1) {
			if (stat & 1) {
				irqno = bast_pc104_irqs[i];
				generic_handle_irq(irqno);
			}
		}
	}
}