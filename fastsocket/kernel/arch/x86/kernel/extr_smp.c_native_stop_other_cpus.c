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
struct TYPE_2__ {int /*<<< orphan*/  (* send_IPI_allbutself ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  REBOOT_VECTOR ; 
 unsigned long USEC_PER_SEC ; 
 TYPE_1__* apic ; 
 int /*<<< orphan*/  disable_local_APIC () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int num_online_cpus () ; 
 scalar_t__ reboot_force ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void native_stop_other_cpus(int wait)
{
	unsigned long flags;
	unsigned long timeout;

	if (reboot_force)
		return;

	/*
	 * Use an own vector here because smp_call_function
	 * does lots of things not suitable in a panic situation.
	 * On most systems we could also use an NMI here,
	 * but there are a few systems around where NMI
	 * is problematic so stay with an non NMI for now
	 * (this implies we cannot stop CPUs spinning with irq off
	 * currently)
	 */
	if (num_online_cpus() > 1) {
		apic->send_IPI_allbutself(REBOOT_VECTOR);

		/*
		 * Don't wait longer than a second if the caller
		 * didn't ask us to wait.
		 */
		timeout = USEC_PER_SEC;
		while (num_online_cpus() > 1 && (wait || timeout--))
			udelay(1);
	}

	local_irq_save(flags);
	disable_local_APIC();
	local_irq_restore(flags);
}