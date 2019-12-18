#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cpu_running; } ;
typedef  TYPE_1__ cpu_data_t ;
struct TYPE_5__ {int /*<<< orphan*/  logical_cpu; int /*<<< orphan*/  physical_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cpu_signal_handler_internal (int /*<<< orphan*/ ) ; 
 TYPE_1__* getCpuDatap () ; 
 int /*<<< orphan*/  hw_atomic_sub (int /*<<< orphan*/ *,int) ; 
 TYPE_2__ machine_info ; 

void
ml_cpu_down(void)
{
	cpu_data_t	*cpu_data_ptr;

	hw_atomic_sub(&machine_info.physical_cpu, 1);
	hw_atomic_sub(&machine_info.logical_cpu, 1);

	/*
	 * If we want to deal with outstanding IPIs, we need to
	 * do relatively early in the processor_doshutdown path,
	 * as we pend decrementer interrupts using the IPI
	 * mechanism if we cannot immediately service them (if
	 * IRQ is masked).  Do so now.
	 *
	 * We aren't on the interrupt stack here; would it make
	 * more sense to disable signaling and then enable
	 * interrupts?  It might be a bit cleaner.
	 */
	cpu_data_ptr = getCpuDatap();
	cpu_data_ptr->cpu_running = FALSE;
	cpu_signal_handler_internal(TRUE);
}