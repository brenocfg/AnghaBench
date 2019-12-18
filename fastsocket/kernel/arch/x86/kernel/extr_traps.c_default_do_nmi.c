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
 int /*<<< orphan*/  DIE_NMI ; 
 int /*<<< orphan*/  DIE_NMI_IPI ; 
 scalar_t__ NOTIFY_STOP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  do_nmi_callback (struct pt_regs*,int) ; 
 unsigned char get_nmi_reason () ; 
 int /*<<< orphan*/  io_check_error (unsigned char,struct pt_regs*) ; 
 int /*<<< orphan*/  mem_parity_error (unsigned char,struct pt_regs*) ; 
 scalar_t__ nmi_watchdog_tick (struct pt_regs*,unsigned char) ; 
 scalar_t__ notify_die (int /*<<< orphan*/ ,char*,struct pt_regs*,unsigned char,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reassert_nmi () ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  unknown_nmi_error (unsigned char,struct pt_regs*) ; 

void default_do_nmi(struct pt_regs *regs)
{
	unsigned char reason = 0;
	int cpu;

	cpu = smp_processor_id();

	/* Only the BSP gets external NMIs from the system. */
	if (!cpu)
		reason = get_nmi_reason();

	if (!(reason & 0xc0)) {
		if (notify_die(DIE_NMI_IPI, "nmi_ipi", regs, reason, 2, SIGINT)
								== NOTIFY_STOP)
			return;

#ifdef CONFIG_X86_LOCAL_APIC
		if (notify_die(DIE_NMI, "nmi", regs, reason, 2, SIGINT)
							== NOTIFY_STOP)
			return;

#ifndef CONFIG_LOCKUP_DETECTOR
		/*
		 * Ok, so this is none of the documented NMI sources,
		 * so it must be the NMI watchdog.
		 */
		if (nmi_watchdog_tick(regs, reason))
			return;
		if (!do_nmi_callback(regs, cpu))
#endif /* !CONFIG_LOCKUP_DETECTOR */
			unknown_nmi_error(reason, regs);
#else
		unknown_nmi_error(reason, regs);
#endif

		return;
	}
	if (notify_die(DIE_NMI, "nmi", regs, reason, 2, SIGINT) == NOTIFY_STOP)
		return;

	/* AK: following checks seem to be broken on modern chipsets. FIXME */
	if (reason & 0x80)
		mem_parity_error(reason, regs);
	if (reason & 0x40)
		io_check_error(reason, regs);
#ifdef CONFIG_X86_32
	/*
	 * Reassert NMI in case it became active meanwhile
	 * as it's edge-triggered:
	 */
	reassert_nmi();
#endif
}