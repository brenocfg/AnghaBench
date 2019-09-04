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

void machine_lockdown(void)
{
#if CONFIG_KERNEL_INTEGRITY
#if KERNEL_INTEGRITY_WT
	/* Watchtower
	 *
	 * Notify the monitor about the completion of early kernel bootstrap.
	 * From this point forward it will enforce the integrity of kernel text,
	 * rodata and page tables.
	 */

#ifdef MONITOR
	monitor_call(MONITOR_LOCKDOWN, 0, 0, 0);
#endif
#endif /* KERNEL_INTEGRITY_WT */


#if defined(KERNEL_INTEGRITY_KTRR)
	/* KTRR
	 *
	 * Lock physical KTRR region. KTRR region is read-only. Memory outside
	 * the region is not executable at EL1.
	 */

	rorgn_lockdown();
#endif /* defined(KERNEL_INTEGRITY_KTRR)*/


#endif /* CONFIG_KERNEL_INTEGRITY */
}