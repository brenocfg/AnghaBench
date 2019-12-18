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
 unsigned int CPU_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int IRQ_TIMER1 ; 
 int /*<<< orphan*/  TIMER_TOPSTAT ; 
 int /*<<< orphan*/  TIMER_VIRT ; 
 unsigned int TSTAT_T0INT ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 int /*<<< orphan*/  timer_tick () ; 

__attribute__((used)) static void
h7202_timerx_demux_handler(unsigned int irq_unused, struct irq_desc *desc)
{
	unsigned int mask, irq;

	mask = CPU_REG (TIMER_VIRT, TIMER_TOPSTAT);

	if ( mask & TSTAT_T0INT ) {
		timer_tick();
		if( mask == TSTAT_T0INT )
			return;
	}

	mask >>= 1;
	irq = IRQ_TIMER1;
	while (mask) {
		if (mask & 1)
			generic_handle_irq(irq);
		irq++;
		mask >>= 1;
	}
}