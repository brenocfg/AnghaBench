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
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int* irqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  do_timer (int) ; 
 int /*<<< orphan*/  get_irq_regs () ; 
 int /*<<< orphan*/  intersil_clear () ; 
 TYPE_1__ kstat_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * led_pattern ; 
 int* sun3_intreg ; 
 int /*<<< orphan*/  sun3_leds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_process_times (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t sun3_int5(int irq, void *dev_id)
{
#ifdef CONFIG_SUN3
	intersil_clear();
#endif
        *sun3_intreg |=  (1 << irq);
#ifdef CONFIG_SUN3
	intersil_clear();
#endif
        do_timer(1);
#ifndef CONFIG_SMP
	update_process_times(user_mode(get_irq_regs()));
#endif
        if (!(kstat_cpu(0).irqs[irq] % 20))
                sun3_leds(led_pattern[(kstat_cpu(0).irqs[irq] % 160) / 20]);
	return IRQ_HANDLED;
}