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
typedef  int uint64_t ;
typedef  void* boolean_t ;
struct TYPE_2__ {void* cpu_NMI_acknowledged; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  NMIPI_enable (void*) ; 
 void* TRUE ; 
 int /*<<< orphan*/  cpu_NMI_interrupt (unsigned int) ; 
 TYPE_1__* cpu_datap (unsigned int) ; 
 int /*<<< orphan*/  cpu_is_running (unsigned int) ; 
 int /*<<< orphan*/  cpu_pause () ; 
 int /*<<< orphan*/  handle_pending_TLB_flushes () ; 
 int /*<<< orphan*/  machine_timeout_suspended () ; 
 void* ml_set_interrupts_enabled (void*) ; 
 int /*<<< orphan*/  panic (char*,unsigned int) ; 
 int rdtsc64 () ; 
 unsigned int real_ncpus ; 

void
NMI_cpus(void)
{
	unsigned int	cpu;
	boolean_t	intrs_enabled;
	uint64_t	tsc_timeout;

	intrs_enabled = ml_set_interrupts_enabled(FALSE);
	NMIPI_enable(TRUE);
	for (cpu = 0; cpu < real_ncpus; cpu++) {
		if (!cpu_is_running(cpu))
			continue;
		cpu_datap(cpu)->cpu_NMI_acknowledged = FALSE;
		cpu_NMI_interrupt(cpu);
		tsc_timeout = !machine_timeout_suspended() ?
				rdtsc64() + (1000 * 1000 * 1000 * 10ULL) :
				~0ULL;
		while (!cpu_datap(cpu)->cpu_NMI_acknowledged) {
			handle_pending_TLB_flushes();
			cpu_pause();
			if (rdtsc64() > tsc_timeout)
				panic("NMI_cpus() timeout cpu %d", cpu);
		}
		cpu_datap(cpu)->cpu_NMI_acknowledged = FALSE;
	}
	NMIPI_enable(FALSE);

	ml_set_interrupts_enabled(intrs_enabled);
}