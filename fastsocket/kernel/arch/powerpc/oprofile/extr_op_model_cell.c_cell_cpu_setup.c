#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct op_counter_config {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  debug_bus_control; int /*<<< orphan*/  group_control; } ;
struct TYPE_3__ {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUM_INTERVAL_CYC ; 
 scalar_t__ SPU_PROFILING_CYCLES ; 
 scalar_t__ SPU_PROFILING_EVENTS ; 
 int /*<<< orphan*/  cbe_cpu_to_node (size_t) ; 
 int /*<<< orphan*/  cbe_disable_pm (size_t) ; 
 int /*<<< orphan*/  cbe_disable_pm_interrupts (size_t) ; 
 scalar_t__ cbe_get_hw_thread_id (size_t) ; 
 int /*<<< orphan*/  cbe_write_pm (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ctr_enabled ; 
 int /*<<< orphan*/  debug_bus_control ; 
 int /*<<< orphan*/  group_control ; 
 int num_counters ; 
 int /*<<< orphan*/  pm_interval ; 
 TYPE_2__ pm_regs ; 
 int pm_rtas_activate_signals (int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__* pm_signal ; 
 int /*<<< orphan*/  pm_start_stop ; 
 scalar_t__ profiling_mode ; 
 size_t smp_processor_id () ; 
 int /*<<< orphan*/  write_pm_cntrl (size_t) ; 

__attribute__((used)) static int cell_cpu_setup(struct op_counter_config *cntr)
{
	u32 cpu = smp_processor_id();
	u32 num_enabled = 0;
	int i;
	int ret;

	/* Cycle based SPU profiling does not use the performance
	 * counters.  The trace array is configured to collect
	 * the data.
	 */
	if (profiling_mode == SPU_PROFILING_CYCLES)
		return 0;

	/* There is one performance monitor per processor chip (i.e. node),
	 * so we only need to perform this function once per node.
	 */
	if (cbe_get_hw_thread_id(cpu))
		return 0;

	/* Stop all counters */
	cbe_disable_pm(cpu);
	cbe_disable_pm_interrupts(cpu);

	cbe_write_pm(cpu, pm_start_stop, 0);
	cbe_write_pm(cpu, group_control, pm_regs.group_control);
	cbe_write_pm(cpu, debug_bus_control, pm_regs.debug_bus_control);
	write_pm_cntrl(cpu);

	for (i = 0; i < num_counters; ++i) {
		if (ctr_enabled & (1 << i)) {
			pm_signal[num_enabled].cpu = cbe_cpu_to_node(cpu);
			num_enabled++;
		}
	}

	/*
	 * The pm_rtas_activate_signals will return -EIO if the FW
	 * call failed.
	 */
	if (profiling_mode == SPU_PROFILING_EVENTS) {
		/* For SPU event profiling also need to setup the
		 * pm interval timer
		 */
		ret = pm_rtas_activate_signals(cbe_cpu_to_node(cpu),
					       num_enabled+2);
		/* store PC from debug bus to Trace buffer as often
		 * as possible (every 10 cycles)
		 */
		cbe_write_pm(cpu, pm_interval, NUM_INTERVAL_CYC);
		return ret;
	} else
		return pm_rtas_activate_signals(cbe_cpu_to_node(cpu),
						num_enabled);
}