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
 int /*<<< orphan*/  PNX8550_INT_TIMER1 ; 
 int /*<<< orphan*/  PNX8550_INT_TIMER2 ; 
 int /*<<< orphan*/  PNX8550_INT_TIMER3 ; 
 int /*<<< orphan*/  do_IRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int read_c0_config7 () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void timer_irqdispatch(int irq)
{
	irq = (0x01c0 & read_c0_config7()) >> 6;

	if (unlikely(irq == 0)) {
		printk("timer_irqdispatch: irq 0, spurious interrupt?\n");
		return;
	}

	if (irq & 0x1)
		do_IRQ(PNX8550_INT_TIMER1);
	if (irq & 0x2)
		do_IRQ(PNX8550_INT_TIMER2);
	if (irq & 0x4)
		do_IRQ(PNX8550_INT_TIMER3);
}