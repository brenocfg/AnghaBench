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
 TYPE_1__ kstat_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * led_pattern ; 
 int* sun3_intreg ; 
 int /*<<< orphan*/  sun3_leds (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t sun3_int7(int irq, void *dev_id)
{
	*sun3_intreg |=  (1 << irq);
	if (!(kstat_cpu(0).irqs[irq] % 2000))
		sun3_leds(led_pattern[(kstat_cpu(0).irqs[irq] % 16000) / 2000]);
	return IRQ_HANDLED;
}