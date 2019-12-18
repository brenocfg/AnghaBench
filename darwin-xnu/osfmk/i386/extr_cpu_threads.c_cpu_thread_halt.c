#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ active_lcpus; } ;
typedef  TYPE_2__ x86_core_t ;
struct TYPE_6__ {TYPE_2__* core; } ;
struct TYPE_8__ {TYPE_1__ lcpu; } ;
typedef  TYPE_3__ cpu_data_t ;
struct TYPE_9__ {int logical_cpu; int physical_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PM_HALT_NORMAL ; 
 TYPE_3__* current_cpu_datap () ; 
 TYPE_4__ machine_info ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_safe_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmCPUHalt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x86_topo_lock ; 

__attribute__((noreturn))
void
cpu_thread_halt(void)
{
    x86_core_t	*core;
    cpu_data_t	*cpup = current_cpu_datap();

    mp_safe_spin_lock(&x86_topo_lock);
    machine_info.logical_cpu -= 1;
    core = cpup->lcpu.core;
    core->active_lcpus -= 1;
    if (core->active_lcpus == 0)
	machine_info.physical_cpu -= 1;
    simple_unlock(&x86_topo_lock);

    /*
     * Let the power management code determine the best way to "stop"
     * the processor.
     */
    ml_set_interrupts_enabled(FALSE);
    while (1) {
	pmCPUHalt(PM_HALT_NORMAL);
    }
    /* NOT REACHED */
}