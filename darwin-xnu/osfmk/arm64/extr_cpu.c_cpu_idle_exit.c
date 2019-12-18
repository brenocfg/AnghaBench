#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  (* processor_idle_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;
struct TYPE_9__ {scalar_t__ idle_timer_notify; int idle_timer_deadline; int /*<<< orphan*/  cpu_id; scalar_t__ cpu_idle_notify; TYPE_2__* cpu_active_thread; } ;
typedef  TYPE_3__ cpu_data_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_8__ {TYPE_1__* map; } ;
struct TYPE_7__ {int /*<<< orphan*/  pmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Idle_load_context () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clock_absolutetime_interval_to_deadline (int,int*) ; 
 int /*<<< orphan*/  configure_coresight_registers (TYPE_3__*) ; 
 scalar_t__ exception_stack_pointer () ; 
 TYPE_3__* getCpuDatap () ; 
 int /*<<< orphan*/  kpc_idle_exit () ; 
 int /*<<< orphan*/  mt_cpu_run (TYPE_3__*) ; 
 int /*<<< orphan*/  pmap_switch_user_ttb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  timer_resync_deadlines () ; 

void
cpu_idle_exit(boolean_t from_reset)
{
	uint64_t	new_idle_timeout_ticks = 0x0ULL;
	cpu_data_t     *cpu_data_ptr = getCpuDatap();

	assert(exception_stack_pointer() != 0);

	/* Back from WFI, unlock OSLAR and EDLAR. */
	if (from_reset)
		configure_coresight_registers(cpu_data_ptr);

#if KPC
	kpc_idle_exit();
#endif

#if MONOTONIC
	mt_cpu_run(cpu_data_ptr);
#endif /* MONOTONIC */

	pmap_switch_user_ttb(cpu_data_ptr->cpu_active_thread->map->pmap);

	if (cpu_data_ptr->cpu_idle_notify)
		((processor_idle_t) cpu_data_ptr->cpu_idle_notify) (cpu_data_ptr->cpu_id, FALSE, &new_idle_timeout_ticks);

	if (cpu_data_ptr->idle_timer_notify != 0) {
		if (new_idle_timeout_ticks == 0x0ULL) {
			/* turn off the idle timer */
			cpu_data_ptr->idle_timer_deadline = 0x0ULL;
		} else {
			/* set the new idle timeout */
			clock_absolutetime_interval_to_deadline(new_idle_timeout_ticks, &cpu_data_ptr->idle_timer_deadline);
		}
		timer_resync_deadlines();
	}

	Idle_load_context();
}