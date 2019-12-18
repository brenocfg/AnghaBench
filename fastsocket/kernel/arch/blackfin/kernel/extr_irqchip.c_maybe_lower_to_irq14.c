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
 int /*<<< orphan*/  CSYNC () ; 
 int bfin_read_IPEND () ; 
 int /*<<< orphan*/  lower_to_irq14 () ; 

__attribute__((used)) static void maybe_lower_to_irq14(void)
{
	unsigned short pending, other_ints;

	/*
	 * If we're the only interrupt running (ignoring IRQ15 which
	 * is for syscalls), lower our priority to IRQ14 so that
	 * softirqs run at that level.  If there's another,
	 * lower-level interrupt, irq_exit will defer softirqs to
	 * that. If the interrupt pipeline is enabled, we are already
	 * running at IRQ14 priority, so we don't need this code.
	 */
	CSYNC();
	pending = bfin_read_IPEND() & ~0x8000;
	other_ints = pending & (pending - 1);
	if (other_ints == 0)
		lower_to_irq14();
}