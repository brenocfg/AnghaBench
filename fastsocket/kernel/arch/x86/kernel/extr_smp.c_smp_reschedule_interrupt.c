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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __smp_reschedule_interrupt () ; 
 int /*<<< orphan*/  ack_APIC_irq () ; 

void smp_reschedule_interrupt(struct pt_regs *regs)
{
	ack_APIC_irq();
	__smp_reschedule_interrupt();
	/*
	 * KVM uses this interrupt to force a cpu out of guest mode
	 */
}