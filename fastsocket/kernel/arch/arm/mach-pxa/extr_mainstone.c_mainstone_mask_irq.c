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
 unsigned int MAINSTONE_IRQ (int /*<<< orphan*/ ) ; 
 int MST_INTMSKENA ; 
 int mainstone_irq_enabled ; 

__attribute__((used)) static void mainstone_mask_irq(unsigned int irq)
{
	int mainstone_irq = (irq - MAINSTONE_IRQ(0));
	MST_INTMSKENA = (mainstone_irq_enabled &= ~(1 << mainstone_irq));
}