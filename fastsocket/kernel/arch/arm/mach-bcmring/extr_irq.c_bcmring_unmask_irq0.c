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
 scalar_t__ INTCHW_INTENABLE ; 
 unsigned int IRQ_INTC0_START ; 
 scalar_t__ MM_IO_BASE_INTC0 ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void bcmring_unmask_irq0(unsigned int irq)
{
	writel(1 << (irq - IRQ_INTC0_START),
	       MM_IO_BASE_INTC0 + INTCHW_INTENABLE);
}