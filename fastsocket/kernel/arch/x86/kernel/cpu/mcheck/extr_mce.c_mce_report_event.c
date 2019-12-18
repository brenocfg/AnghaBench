#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* send_IPI_self ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MCE_SELF_VECTOR ; 
 int X86_EFLAGS_IF ; 
 int X86_VM_MASK ; 
 TYPE_1__* apic ; 
 int /*<<< orphan*/  apic_wait_icr_idle () ; 
 int /*<<< orphan*/  cpu_has_apic ; 
 int /*<<< orphan*/  mce_notify_irq () ; 
 int /*<<< orphan*/  mce_schedule_work () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mce_report_event(struct pt_regs *regs)
{
	if (regs->flags & (X86_VM_MASK|X86_EFLAGS_IF)) {
		mce_notify_irq();
		/*
		 * Triggering the work queue here is just an insurance
		 * policy in case the syscall exit notify handler
		 * doesn't run soon enough or ends up running on the
		 * wrong CPU (can happen when audit sleeps)
		 */
		mce_schedule_work();
		return;
	}

#ifdef CONFIG_X86_LOCAL_APIC
	/*
	 * Without APIC do not notify. The event will be picked
	 * up eventually.
	 */
	if (!cpu_has_apic)
		return;

	/*
	 * When interrupts are disabled we cannot use
	 * kernel services safely. Trigger an self interrupt
	 * through the APIC to instead do the notification
	 * after interrupts are reenabled again.
	 */
	apic->send_IPI_self(MCE_SELF_VECTOR);

	/*
	 * Wait for idle afterwards again so that we don't leave the
	 * APIC in a non idle state because the normal APIC writes
	 * cannot exclude us.
	 */
	apic_wait_icr_idle();
#endif
}