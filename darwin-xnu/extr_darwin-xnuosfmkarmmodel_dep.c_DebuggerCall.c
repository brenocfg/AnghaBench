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

void
DebuggerCall(
	unsigned int	reason,
	void		*ctx)
{
#if	!MACH_KDP
#pragma unused(reason,ctx)
#endif /* !MACH_KDP */

#if ALTERNATE_DEBUGGER
	alternate_debugger_enter();
#endif

#if	MACH_KDP
	kdp_trap(reason, (struct arm_saved_state *)ctx);
#else
	/* TODO: decide what to do if no debugger config */
#endif
}