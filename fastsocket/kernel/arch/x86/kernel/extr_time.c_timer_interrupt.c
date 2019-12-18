#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* event_handler ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ MCA_bus ; 
 int /*<<< orphan*/  PIC_MASTER_OCW3 ; 
 int /*<<< orphan*/  PIC_MASTER_POLL ; 
 TYPE_1__* global_clock_event ; 
 int /*<<< orphan*/  i8259A_lock ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int inb_p (int) ; 
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq0_irqs ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 scalar_t__ timer_ack ; 

__attribute__((used)) static irqreturn_t timer_interrupt(int irq, void *dev_id)
{
	/* Keep nmi watchdog up to date */
	inc_irq_stat(irq0_irqs);

	/* Optimized out for !IO_APIC and x86_64 */
	if (timer_ack) {
		/*
		 * Subtle, when I/O APICs are used we have to ack timer IRQ
		 * manually to deassert NMI lines for the watchdog if run
		 * on an 82489DX-based system.
		 */
		spin_lock(&i8259A_lock);
		outb(0x0c, PIC_MASTER_OCW3);
		/* Ack the IRQ; AEOI will end it automatically. */
		inb(PIC_MASTER_POLL);
		spin_unlock(&i8259A_lock);
	}

	global_clock_event->event_handler(global_clock_event);

	/* MCA bus quirk: Acknowledge irq0 by setting bit 7 in port 0x61 */
	if (MCA_bus)
		outb_p(inb_p(0x61)| 0x80, 0x61);

	return IRQ_HANDLED;
}