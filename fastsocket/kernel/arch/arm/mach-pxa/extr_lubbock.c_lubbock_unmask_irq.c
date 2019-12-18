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
 unsigned int LUBBOCK_IRQ (int /*<<< orphan*/ ) ; 
 int LUB_IRQ_MASK_EN ; 
 int LUB_IRQ_SET_CLR ; 
 int lubbock_irq_enabled ; 

__attribute__((used)) static void lubbock_unmask_irq(unsigned int irq)
{
	int lubbock_irq = (irq - LUBBOCK_IRQ(0));
	/* the irq can be acknowledged only if deasserted, so it's done here */
	LUB_IRQ_SET_CLR &= ~(1 << lubbock_irq);
	LUB_IRQ_MASK_EN = (lubbock_irq_enabled |= (1 << lubbock_irq));
}