#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ active_lcpus; } ;
typedef  TYPE_2__ x86_core_t ;
struct TYPE_8__ {TYPE_2__* core; } ;
struct TYPE_10__ {TYPE_1__ lcpu; } ;
typedef  TYPE_3__ cpu_data_t ;
struct TYPE_11__ {int logical_cpu; int physical_cpu; } ;

/* Variables and functions */
 TYPE_2__* cpu_thread_alloc (int) ; 
 TYPE_3__* current_cpu_datap () ; 
 int get_cpu_number () ; 
 TYPE_5__ machine_info ; 
 int master_cpu ; 
 int /*<<< orphan*/  mp_safe_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmCPUMarkRunning (TYPE_3__*) ; 
 int /*<<< orphan*/  simple_lock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_resync_deadlines () ; 
 int /*<<< orphan*/  x86_topo_lock ; 

void
cpu_thread_init(void)
{
    int		my_cpu		= get_cpu_number();
    cpu_data_t	*cpup		= current_cpu_datap();
    x86_core_t	*core;
    static int	initialized	= 0;

    /*
     * If we're the boot processor, we do all of the initialization of
     * the CPU topology infrastructure.
     */
    if (my_cpu == master_cpu && !initialized) {
	simple_lock_init(&x86_topo_lock, 0);

	/*
	 * Put this logical CPU into the physical CPU topology.
	 */
	cpup->lcpu.core = cpu_thread_alloc(my_cpu);

	initialized = 1;
    }

    /*
     * Do the CPU accounting.
     */
    core = cpup->lcpu.core;
    mp_safe_spin_lock(&x86_topo_lock);
    machine_info.logical_cpu += 1;
    if (core->active_lcpus == 0)
	machine_info.physical_cpu += 1;
    core->active_lcpus += 1;
    simple_unlock(&x86_topo_lock);

    pmCPUMarkRunning(cpup);
    timer_resync_deadlines();
}