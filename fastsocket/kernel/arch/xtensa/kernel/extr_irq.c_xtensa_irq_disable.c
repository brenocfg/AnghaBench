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
 int /*<<< orphan*/  variant_irq_disable (unsigned int) ; 
 int /*<<< orphan*/  xtensa_irq_mask (unsigned int) ; 

__attribute__((used)) static void xtensa_irq_disable(unsigned int irq)
{
	xtensa_irq_mask(irq);
	variant_irq_disable(irq);
}