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
typedef  unsigned long* vulp ;

/* Variables and functions */
 scalar_t__ PYXIS_INT_MASK ; 
 scalar_t__ PYXIS_INT_REQ ; 
 unsigned long cached_irq_mask ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
pyxis_mask_and_ack_irq(unsigned int irq)
{
	unsigned long bit = 1UL << (irq - 16);
	unsigned long mask = cached_irq_mask &= ~bit;

	/* Disable the interrupt.  */
	*(vulp)PYXIS_INT_MASK = mask;
	wmb();
	/* Ack PYXIS PCI interrupt.  */
	*(vulp)PYXIS_INT_REQ = bit;
	mb();
	/* Re-read to force both writes.  */
	*(vulp)PYXIS_INT_MASK;
}