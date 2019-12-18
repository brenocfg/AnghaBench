#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct TYPE_3__ {int /*<<< orphan*/  cpu_id; int /*<<< orphan*/ * cpu_user_debug; int /*<<< orphan*/  cpu_flags; scalar_t__ cpu_reset_handler; int /*<<< orphan*/  cpu_active_thread; } ;
typedef  TYPE_1__ cpu_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  CleanPoC_Dcache () ; 
 int /*<<< orphan*/  PE_cpu_machine_quiesce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SleepState ; 
 int /*<<< orphan*/  current_thread () ; 
 TYPE_1__* getCpuDatap () ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  pmap_switch_user_ttb (int /*<<< orphan*/ ) ; 
 scalar_t__ start_cpu_paddr ; 

void
cpu_sleep(void)
{
	cpu_data_t     *cpu_data_ptr = getCpuDatap();
	pmap_switch_user_ttb(kernel_pmap);
	cpu_data_ptr->cpu_active_thread = current_thread();
	cpu_data_ptr->cpu_reset_handler = (vm_offset_t) start_cpu_paddr;
	cpu_data_ptr->cpu_flags |= SleepState;
	cpu_data_ptr->cpu_user_debug = NULL;

	CleanPoC_Dcache();

	PE_cpu_machine_quiesce(cpu_data_ptr->cpu_id);

}