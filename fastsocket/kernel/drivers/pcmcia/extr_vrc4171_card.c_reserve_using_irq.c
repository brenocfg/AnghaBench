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
 int /*<<< orphan*/  I365_CSCINT ; 
 int /*<<< orphan*/  I365_INTCTL ; 
 unsigned int exca_read_byte (int,int /*<<< orphan*/ ) ; 
 int vrc4171_irq_mask ; 

__attribute__((used)) static inline void reserve_using_irq(int slot)
{
	unsigned int irq;

	irq = exca_read_byte(slot, I365_INTCTL);
	irq &= 0x0f;
	vrc4171_irq_mask &= ~(1 << irq);

	irq = exca_read_byte(slot, I365_CSCINT);
	irq = (irq & 0xf0) >> 4;
	vrc4171_irq_mask &= ~(1 << irq);
}