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
 int /*<<< orphan*/  ICU_INT_CONF (unsigned int) ; 
 int IRQ_ROUTE_TO_AP ; 
 int PRIORITY_DEFAULT ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void icu_unmask_irq(unsigned int irq)
{
	__raw_writel(IRQ_ROUTE_TO_AP | PRIORITY_DEFAULT, ICU_INT_CONF(irq));
}