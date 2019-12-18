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
 unsigned int* cached_irq_mask ; 
 int /*<<< orphan*/  outb (unsigned int,int) ; 

__attribute__((used)) static void shark_disable_8259A_irq(unsigned int irq)
{
	unsigned int mask;
	if (irq<8) {
	  mask = 1 << irq;
	  cached_irq_mask[0] |= mask;
	  outb(cached_irq_mask[1],0xA1);
	} else {
	  mask = 1 << (irq-8);
	  cached_irq_mask[1] |= mask;
	  outb(cached_irq_mask[0],0x21);
	}
}