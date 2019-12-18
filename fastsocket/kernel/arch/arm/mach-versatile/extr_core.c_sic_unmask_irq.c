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
 scalar_t__ IRQ_SIC_START ; 
 scalar_t__ SIC_IRQ_ENABLE_SET ; 
 scalar_t__ VA_SIC_BASE ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void sic_unmask_irq(unsigned int irq)
{
	irq -= IRQ_SIC_START;
	writel(1 << irq, VA_SIC_BASE + SIC_IRQ_ENABLE_SET);
}