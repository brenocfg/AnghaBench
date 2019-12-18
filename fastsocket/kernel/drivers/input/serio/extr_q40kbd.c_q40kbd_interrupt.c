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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTERRUPT_REG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  KEYBOARD_UNLOCK_REG ; 
 int /*<<< orphan*/  KEYCODE_REG ; 
 int Q40_IRQ_KEYB_MASK ; 
 int master_inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  master_outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q40kbd_lock ; 
 int /*<<< orphan*/  q40kbd_port ; 
 int /*<<< orphan*/  serio_interrupt (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t q40kbd_interrupt(int irq, void *dev_id)
{
	unsigned long flags;

	spin_lock_irqsave(&q40kbd_lock, flags);

	if (Q40_IRQ_KEYB_MASK & master_inb(INTERRUPT_REG))
		serio_interrupt(q40kbd_port, master_inb(KEYCODE_REG), 0);

	master_outb(-1, KEYBOARD_UNLOCK_REG);

	spin_unlock_irqrestore(&q40kbd_lock, flags);

	return IRQ_HANDLED;
}