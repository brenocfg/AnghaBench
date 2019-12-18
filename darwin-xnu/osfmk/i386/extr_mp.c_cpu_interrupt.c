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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MACH_SCHED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_REMOTE_AST ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cpu_datap (int) ; 
 int /*<<< orphan*/  i386_cpu_IPI (int) ; 
 scalar_t__ pmCPUExitIdle (int /*<<< orphan*/ ) ; 
 scalar_t__ smp_initialized ; 

void
cpu_interrupt(int cpu)
{
	boolean_t did_IPI = FALSE;

	if (smp_initialized
	    && pmCPUExitIdle(cpu_datap(cpu))) {
		i386_cpu_IPI(cpu);
		did_IPI = TRUE;
	}

	KERNEL_DEBUG_CONSTANT(MACHDBG_CODE(DBG_MACH_SCHED, MACH_REMOTE_AST), cpu, did_IPI, 0, 0, 0);
}