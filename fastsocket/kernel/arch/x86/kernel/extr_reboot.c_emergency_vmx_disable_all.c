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
 scalar_t__ cpu_has_vmx () ; 
 scalar_t__ cpu_vmx_enabled () ; 
 int /*<<< orphan*/  cpu_vmxoff () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  nmi_shootdown_cpus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmxoff_nmi ; 

__attribute__((used)) static void emergency_vmx_disable_all(void)
{
	/* Just make sure we won't change CPUs while doing this */
	local_irq_disable();

	/* We need to disable VMX on all CPUs before rebooting, otherwise
	 * we risk hanging up the machine, because the CPU ignore INIT
	 * signals when VMX is enabled.
	 *
	 * We can't take any locks and we may be on an inconsistent
	 * state, so we use NMIs as IPIs to tell the other CPUs to disable
	 * VMX and halt.
	 *
	 * For safety, we will avoid running the nmi_shootdown_cpus()
	 * stuff unnecessarily, but we don't have a way to check
	 * if other CPUs have VMX enabled. So we will call it only if the
	 * CPU we are running on has VMX enabled.
	 *
	 * We will miss cases where VMX is not enabled on all CPUs. This
	 * shouldn't do much harm because KVM always enable VMX on all
	 * CPUs anyway. But we can miss it on the small window where KVM
	 * is still enabling VMX.
	 */
	if (cpu_has_vmx() && cpu_vmx_enabled()) {
		/* Disable VMX on this CPU.
		 */
		cpu_vmxoff();

		/* Halt and disable VMX on the other CPUs */
		nmi_shootdown_cpus(vmxoff_nmi);

	}
}