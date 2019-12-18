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
struct debug_store {int /*<<< orphan*/  bts_buffer_base; int /*<<< orphan*/  bts_index; } ;
struct TYPE_4__ {int /*<<< orphan*/  ds; } ;
struct TYPE_3__ {int num_counters; int num_counters_fixed; } ;

/* Variables and functions */
 scalar_t__ MSR_ARCH_PERFMON_FIXED_CTR0 ; 
 int /*<<< orphan*/  checking_wrmsrl (scalar_t__,unsigned long long) ; 
 TYPE_2__ cpu_hw_events ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct debug_store* percpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 TYPE_1__ x86_pmu ; 
 scalar_t__ x86_pmu_config_addr (int) ; 
 scalar_t__ x86_pmu_event_addr (int) ; 

__attribute__((used)) static void intel_pmu_reset(void)
{
	struct debug_store *ds = percpu_read(cpu_hw_events.ds);
	unsigned long flags;
	int idx;

	if (!x86_pmu.num_counters)
		return;

	local_irq_save(flags);

	printk("clearing PMU state on CPU#%d\n", smp_processor_id());

	for (idx = 0; idx < x86_pmu.num_counters; idx++) {
		checking_wrmsrl(x86_pmu_config_addr(idx), 0ull);
		checking_wrmsrl(x86_pmu_event_addr(idx),  0ull);
	}
	for (idx = 0; idx < x86_pmu.num_counters_fixed; idx++)
		checking_wrmsrl(MSR_ARCH_PERFMON_FIXED_CTR0 + idx, 0ull);

	if (ds)
		ds->bts_index = ds->bts_buffer_base;

	local_irq_restore(flags);
}