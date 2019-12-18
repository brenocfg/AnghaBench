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
 int /*<<< orphan*/ * CSR_IRQ_ENABLE ; 
 size_t _DC21285_INR (unsigned int) ; 
 int /*<<< orphan*/ * fb_irq_mask ; 

__attribute__((used)) static void fb_unmask_irq(unsigned int irq)
{
	*CSR_IRQ_ENABLE = fb_irq_mask[_DC21285_INR(irq)];
}