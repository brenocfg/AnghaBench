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
typedef  int u16 ;
struct irq_desc {TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unmask ) (unsigned int) ;int /*<<< orphan*/  (* ack ) (unsigned int) ;} ;

/* Variables and functions */
 int* IXDP2351_CPLD_INTB_STAT_REG ; 
 scalar_t__ IXDP2351_INTB_IRQ_BASE ; 
 int IXDP2351_INTB_IRQ_NUM ; 
 int IXDP2351_INTB_IRQ_VALID ; 
 int IXP23XX_MACH_IRQ (scalar_t__) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 
 int /*<<< orphan*/  stub2 (unsigned int) ; 

__attribute__((used)) static void ixdp2351_intb_handler(unsigned int irq, struct irq_desc *desc)
{
	u16 ex_interrupt =
		*IXDP2351_CPLD_INTB_STAT_REG & IXDP2351_INTB_IRQ_VALID;
	int i;

	desc->chip->ack(irq);

	for (i = 0; i < IXDP2351_INTB_IRQ_NUM; i++) {
		if (ex_interrupt & (1 << i)) {
			int cpld_irq =
				IXP23XX_MACH_IRQ(IXDP2351_INTB_IRQ_BASE + i);
			generic_handle_irq(cpld_irq);
		}
	}

	desc->chip->unmask(irq);
}