#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* task_t ;
typedef  size_t sfi_class_id_t ;
struct TYPE_6__ {int /*<<< orphan*/  energy_billed_to_others; int /*<<< orphan*/  energy_billed_to_me; int /*<<< orphan*/  logical_writes; int /*<<< orphan*/  physical_writes; int /*<<< orphan*/  cpu_time_billed_to_others; int /*<<< orphan*/  cpu_time_billed_to_me; int /*<<< orphan*/ * sfi_wait_times; int /*<<< orphan*/  interrupt_wakeups; int /*<<< orphan*/  platform_idle_wakeups; int /*<<< orphan*/  cpu_time; } ;
struct TYPE_5__ {int /*<<< orphan*/  ledger; int /*<<< orphan*/  task_energy; int /*<<< orphan*/  task_metadata_writes; int /*<<< orphan*/  task_invalidated_writes; int /*<<< orphan*/  task_deferred_writes; int /*<<< orphan*/  task_immediate_writes; int /*<<< orphan*/  task_gpu_ns; int /*<<< orphan*/  task_timer_wakeups_bin_2; int /*<<< orphan*/  task_timer_wakeups_bin_1; int /*<<< orphan*/  cpu_time_rqos_stats; int /*<<< orphan*/  cpu_time_eqos_stats; int /*<<< orphan*/ * task_io_stats; int /*<<< orphan*/  low_mem_privileged_listener; int /*<<< orphan*/  purged_memory_critical; int /*<<< orphan*/  purged_memory_warn; int /*<<< orphan*/  low_mem_notified_critical; int /*<<< orphan*/  low_mem_notified_warn; int /*<<< orphan*/  extmod_statistics; int /*<<< orphan*/  ps_switch; int /*<<< orphan*/  p_switch; int /*<<< orphan*/  c_switch; int /*<<< orphan*/  syscalls_unix; int /*<<< orphan*/  syscalls_mach; int /*<<< orphan*/  messages_received; int /*<<< orphan*/  messages_sent; int /*<<< orphan*/  cow_faults; int /*<<< orphan*/  pageins; int /*<<< orphan*/  faults; int /*<<< orphan*/  total_runnable_time; int /*<<< orphan*/  total_ptime; int /*<<< orphan*/  total_system_time; int /*<<< orphan*/  total_user_time; } ;

/* Variables and functions */
 size_t MAX_SFI_CLASS_ID ; 
 size_t SFI_CLASS_UNSPECIFIED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ledger_rollup_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ task_ledgers ; 

void
task_rollup_accounting_info(task_t to_task, task_t from_task)
{
	assert(from_task != to_task);

	to_task->total_user_time = from_task->total_user_time;
	to_task->total_system_time = from_task->total_system_time;
	to_task->total_ptime = from_task->total_ptime;
	to_task->total_runnable_time = from_task->total_runnable_time;
	to_task->faults = from_task->faults;
	to_task->pageins = from_task->pageins;
	to_task->cow_faults = from_task->cow_faults;
	to_task->messages_sent = from_task->messages_sent;
	to_task->messages_received = from_task->messages_received;
	to_task->syscalls_mach = from_task->syscalls_mach;
	to_task->syscalls_unix = from_task->syscalls_unix;
	to_task->c_switch = from_task->c_switch;
	to_task->p_switch = from_task->p_switch;
	to_task->ps_switch = from_task->ps_switch;
	to_task->extmod_statistics = from_task->extmod_statistics;
	to_task->low_mem_notified_warn = from_task->low_mem_notified_warn;
	to_task->low_mem_notified_critical = from_task->low_mem_notified_critical;
	to_task->purged_memory_warn = from_task->purged_memory_warn;
	to_task->purged_memory_critical = from_task->purged_memory_critical;
	to_task->low_mem_privileged_listener = from_task->low_mem_privileged_listener;
	*to_task->task_io_stats = *from_task->task_io_stats;
	to_task->cpu_time_eqos_stats = from_task->cpu_time_eqos_stats;
	to_task->cpu_time_rqos_stats = from_task->cpu_time_rqos_stats;
	to_task->task_timer_wakeups_bin_1 = from_task->task_timer_wakeups_bin_1;
	to_task->task_timer_wakeups_bin_2 = from_task->task_timer_wakeups_bin_2;
	to_task->task_gpu_ns = from_task->task_gpu_ns;
	to_task->task_immediate_writes = from_task->task_immediate_writes;
	to_task->task_deferred_writes = from_task->task_deferred_writes;
	to_task->task_invalidated_writes = from_task->task_invalidated_writes;
	to_task->task_metadata_writes = from_task->task_metadata_writes;
	to_task->task_energy = from_task->task_energy;

	/* Skip ledger roll up for memory accounting entries */
	ledger_rollup_entry(to_task->ledger, from_task->ledger, task_ledgers.cpu_time);
	ledger_rollup_entry(to_task->ledger, from_task->ledger, task_ledgers.platform_idle_wakeups);
	ledger_rollup_entry(to_task->ledger, from_task->ledger, task_ledgers.interrupt_wakeups);
#if CONFIG_SCHED_SFI
	for (sfi_class_id_t class_id = SFI_CLASS_UNSPECIFIED; class_id < MAX_SFI_CLASS_ID; class_id++) {
		ledger_rollup_entry(to_task->ledger, from_task->ledger, task_ledgers.sfi_wait_times[class_id]);
	}
#endif
	ledger_rollup_entry(to_task->ledger, from_task->ledger, task_ledgers.cpu_time_billed_to_me);
	ledger_rollup_entry(to_task->ledger, from_task->ledger, task_ledgers.cpu_time_billed_to_others);
	ledger_rollup_entry(to_task->ledger, from_task->ledger, task_ledgers.physical_writes);
	ledger_rollup_entry(to_task->ledger, from_task->ledger, task_ledgers.logical_writes);
	ledger_rollup_entry(to_task->ledger, from_task->ledger, task_ledgers.energy_billed_to_me);
	ledger_rollup_entry(to_task->ledger, from_task->ledger, task_ledgers.energy_billed_to_others);
}