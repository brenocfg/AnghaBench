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
 int IRQ_IDX (unsigned int) ; 
 int scc_mask ; 

__attribute__((used)) static void scc_irq_enable(unsigned int irq)
{
	int irq_idx = IRQ_IDX(irq);

	scc_mask |= (1 << irq_idx);
}