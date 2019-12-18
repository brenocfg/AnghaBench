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
 scalar_t__ MALTA_INT_BASE ; 
 int /*<<< orphan*/  do_IRQ (scalar_t__) ; 
 int get_int () ; 

__attribute__((used)) static void malta_hw0_irqdispatch(void)
{
	int irq;

	irq = get_int();
	if (irq < 0) {
		/* interrupt has already been cleared */
		return;
	}

	do_IRQ(MALTA_INT_BASE + irq);
}