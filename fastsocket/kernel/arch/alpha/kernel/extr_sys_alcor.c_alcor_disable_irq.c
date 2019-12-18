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
 int /*<<< orphan*/  alcor_update_irq_hw (unsigned long) ; 
 unsigned long cached_irq_mask ; 

__attribute__((used)) static void
alcor_disable_irq(unsigned int irq)
{
	alcor_update_irq_hw(cached_irq_mask &= ~(1UL << (irq - 16)));
}