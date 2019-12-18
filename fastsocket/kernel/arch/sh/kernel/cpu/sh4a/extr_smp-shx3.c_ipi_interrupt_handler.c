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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int ctrl_inl (int) ; 
 int /*<<< orphan*/  ctrl_outl (unsigned int,int) ; 
 unsigned int hard_smp_processor_id () ; 
 int /*<<< orphan*/  smp_message_recv (unsigned int) ; 

__attribute__((used)) static irqreturn_t ipi_interrupt_handler(int irq, void *arg)
{
	unsigned int message = (unsigned int)(long)arg;
	unsigned int cpu = hard_smp_processor_id();
	unsigned int offs = 4 * cpu;
	unsigned int x;

	x = ctrl_inl(0xfe410070 + offs); /* C0INITICI..CnINTICI */
	x &= (1 << (message << 2));
	ctrl_outl(x, 0xfe410080 + offs); /* C0INTICICLR..CnINTICICLR */

	smp_message_recv(message);

	return IRQ_HANDLED;
}