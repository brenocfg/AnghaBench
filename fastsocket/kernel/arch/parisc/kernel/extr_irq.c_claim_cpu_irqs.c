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
struct TYPE_2__ {void* status; int /*<<< orphan*/ * action; int /*<<< orphan*/ * chip; } ;

/* Variables and functions */
 int CPU_IRQ_BASE ; 
 int CPU_IRQ_MAX ; 
 size_t IPI_IRQ ; 
 void* IRQ_PER_CPU ; 
 size_t TIMER_IRQ ; 
 int /*<<< orphan*/  cpu_interrupt_type ; 
 int /*<<< orphan*/  ipi_action ; 
 TYPE_1__* irq_desc ; 
 int /*<<< orphan*/  timer_action ; 

__attribute__((used)) static void claim_cpu_irqs(void)
{
	int i;
	for (i = CPU_IRQ_BASE; i <= CPU_IRQ_MAX; i++) {
		irq_desc[i].chip = &cpu_interrupt_type;
	}

	irq_desc[TIMER_IRQ].action = &timer_action;
	irq_desc[TIMER_IRQ].status = IRQ_PER_CPU;
#ifdef CONFIG_SMP
	irq_desc[IPI_IRQ].action = &ipi_action;
	irq_desc[IPI_IRQ].status = IRQ_PER_CPU;
#endif
}