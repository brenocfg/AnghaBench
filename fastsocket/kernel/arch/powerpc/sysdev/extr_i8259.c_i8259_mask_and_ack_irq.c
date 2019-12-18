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
 int cached_21 ; 
 int cached_A1 ; 
 int /*<<< orphan*/  i8259_lock ; 
 int /*<<< orphan*/  inb (int) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void i8259_mask_and_ack_irq(unsigned int irq_nr)
{
	unsigned long flags;

	spin_lock_irqsave(&i8259_lock, flags);
	if (irq_nr > 7) {
		cached_A1 |= 1 << (irq_nr-8);
		inb(0xA1); 	/* DUMMY */
		outb(cached_A1, 0xA1);
		outb(0x20, 0xA0);	/* Non-specific EOI */
		outb(0x20, 0x20);	/* Non-specific EOI to cascade */
	} else {
		cached_21 |= 1 << irq_nr;
		inb(0x21); 	/* DUMMY */
		outb(cached_21, 0x21);
		outb(0x20, 0x20);	/* Non-specific EOI */
	}
	spin_unlock_irqrestore(&i8259_lock, flags);
}