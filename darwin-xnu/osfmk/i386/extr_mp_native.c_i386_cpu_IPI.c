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
struct TYPE_2__ {int cpu_signals; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERPROCESSOR ; 
 int /*<<< orphan*/  LAPIC_VECTOR (int /*<<< orphan*/ ) ; 
 TYPE_1__* cpu_datap (int) ; 
 int /*<<< orphan*/  kprintf (char*,int,int) ; 
 int /*<<< orphan*/  lapic_send_ipi (int,int /*<<< orphan*/ ) ; 

void
i386_cpu_IPI(int cpu)
{
#ifdef	MP_DEBUG
	if(cpu_datap(cpu)->cpu_signals & 6) {	/* (BRINGUP) */
		kprintf("i386_cpu_IPI: sending enter debugger signal (%08X) to cpu %d\n", cpu_datap(cpu)->cpu_signals, cpu);
	}
#endif	/* MP_DEBUG */

	lapic_send_ipi(cpu, LAPIC_VECTOR(INTERPROCESSOR));
}