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
typedef  int /*<<< orphan*/ * ledger_template_t ;
struct TYPE_2__ {scalar_t__ cpu_time; scalar_t__ tkm_private; scalar_t__ tkm_shared; scalar_t__ phys_mem; scalar_t__ wired_mem; scalar_t__ internal; scalar_t__ iokit_mapped; scalar_t__ alternate_accounting; scalar_t__ alternate_accounting_compressed; scalar_t__ page_table; scalar_t__ phys_footprint; scalar_t__ internal_compressed; scalar_t__ purgeable_volatile; scalar_t__ purgeable_nonvolatile; scalar_t__ purgeable_volatile_compressed; scalar_t__ purgeable_nonvolatile_compressed; scalar_t__ network_volatile; scalar_t__ network_nonvolatile; scalar_t__ network_volatile_compressed; scalar_t__ network_nonvolatile_compressed; scalar_t__ platform_idle_wakeups; scalar_t__ interrupt_wakeups; scalar_t__ cpu_time_billed_to_me; scalar_t__ cpu_time_billed_to_others; scalar_t__ physical_writes; scalar_t__ logical_writes; scalar_t__ energy_billed_to_me; scalar_t__ energy_billed_to_others; } ;

/* Variables and functions */
 scalar_t__ FLAVOR_IO_LOGICAL_WRITES ; 
 scalar_t__ FLAVOR_IO_PHYSICAL_WRITES ; 
 scalar_t__ TASK_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ kernel_task ; 
 void* ledger_entry_add (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  ledger_set_callback (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ledger_template_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ledger_template_create (char*) ; 
 int /*<<< orphan*/  ledger_track_credit_only (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ledger_track_maximum (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  task_io_rate_exceeded ; 
 int /*<<< orphan*/ * task_ledger_template ; 
 TYPE_1__ task_ledgers ; 
 int /*<<< orphan*/  task_wakeups_rate_exceeded ; 

void
init_task_ledgers(void)
{
	ledger_template_t t;
	
	assert(task_ledger_template == NULL);
	assert(kernel_task == TASK_NULL);

#if MACH_ASSERT
	PE_parse_boot_argn("pmap_ledgers_panic",
			   &pmap_ledgers_panic,
			  sizeof (pmap_ledgers_panic));
	PE_parse_boot_argn("pmap_ledgers_panic_leeway",
			   &pmap_ledgers_panic_leeway,
			  sizeof (pmap_ledgers_panic_leeway));
#endif /* MACH_ASSERT */

	if ((t = ledger_template_create("Per-task ledger")) == NULL)
		panic("couldn't create task ledger template");

	task_ledgers.cpu_time = ledger_entry_add(t, "cpu_time", "sched", "ns");
	task_ledgers.tkm_private = ledger_entry_add(t, "tkm_private",
	    "physmem", "bytes");
	task_ledgers.tkm_shared = ledger_entry_add(t, "tkm_shared", "physmem",
	    "bytes");
	task_ledgers.phys_mem = ledger_entry_add(t, "phys_mem", "physmem",
	    "bytes");
	task_ledgers.wired_mem = ledger_entry_add(t, "wired_mem", "physmem",
	    "bytes");
	task_ledgers.internal = ledger_entry_add(t, "internal", "physmem",
	    "bytes");
	task_ledgers.iokit_mapped = ledger_entry_add(t, "iokit_mapped", "mappings",
 	    "bytes");
	task_ledgers.alternate_accounting = ledger_entry_add(t, "alternate_accounting", "physmem",
 	    "bytes");
	task_ledgers.alternate_accounting_compressed = ledger_entry_add(t, "alternate_accounting_compressed", "physmem",
 	    "bytes");
	task_ledgers.page_table = ledger_entry_add(t, "page_table", "physmem",
	    "bytes");
	task_ledgers.phys_footprint = ledger_entry_add(t, "phys_footprint", "physmem",
 	    "bytes");
	task_ledgers.internal_compressed = ledger_entry_add(t, "internal_compressed", "physmem",
 	    "bytes");
	task_ledgers.purgeable_volatile = ledger_entry_add(t, "purgeable_volatile", "physmem", "bytes");
	task_ledgers.purgeable_nonvolatile = ledger_entry_add(t, "purgeable_nonvolatile", "physmem", "bytes");
	task_ledgers.purgeable_volatile_compressed = ledger_entry_add(t, "purgeable_volatile_compress", "physmem", "bytes");
	task_ledgers.purgeable_nonvolatile_compressed = ledger_entry_add(t, "purgeable_nonvolatile_compress", "physmem", "bytes");

	task_ledgers.network_volatile = ledger_entry_add(t, "network_volatile", "physmem", "bytes");
	task_ledgers.network_nonvolatile = ledger_entry_add(t, "network_nonvolatile", "physmem", "bytes");
	task_ledgers.network_volatile_compressed = ledger_entry_add(t, "network_volatile_compressed", "physmem", "bytes");
	task_ledgers.network_nonvolatile_compressed = ledger_entry_add(t, "network_nonvolatile_compressed", "physmem", "bytes");

	task_ledgers.platform_idle_wakeups = ledger_entry_add(t, "platform_idle_wakeups", "power",
 	    "count");
	task_ledgers.interrupt_wakeups = ledger_entry_add(t, "interrupt_wakeups", "power",
 	    "count");
	
#if CONFIG_SCHED_SFI
	sfi_class_id_t class_id, ledger_alias;
	for (class_id = SFI_CLASS_UNSPECIFIED; class_id < MAX_SFI_CLASS_ID; class_id++) {
		task_ledgers.sfi_wait_times[class_id] = -1;
	}

	/* don't account for UNSPECIFIED */
	for (class_id = SFI_CLASS_UNSPECIFIED + 1; class_id < MAX_SFI_CLASS_ID; class_id++) {
		ledger_alias = sfi_get_ledger_alias_for_class(class_id);
		if (ledger_alias != SFI_CLASS_UNSPECIFIED) {
			/* Check to see if alias has been registered yet */
			if (task_ledgers.sfi_wait_times[ledger_alias] != -1) {
				task_ledgers.sfi_wait_times[class_id] = task_ledgers.sfi_wait_times[ledger_alias];
			} else {
				/* Otherwise, initialize it first */
				task_ledgers.sfi_wait_times[class_id] = task_ledgers.sfi_wait_times[ledger_alias] = sfi_ledger_entry_add(t, ledger_alias);
			}
		} else {
			task_ledgers.sfi_wait_times[class_id] = sfi_ledger_entry_add(t, class_id);
		}

		if (task_ledgers.sfi_wait_times[class_id] < 0) {
			panic("couldn't create entries for task ledger template for SFI class 0x%x", class_id);
		}
	}

	assert(task_ledgers.sfi_wait_times[MAX_SFI_CLASS_ID -1] != -1);
#endif /* CONFIG_SCHED_SFI */

	task_ledgers.cpu_time_billed_to_me = ledger_entry_add(t, "cpu_time_billed_to_me", "sched", "ns");
	task_ledgers.cpu_time_billed_to_others = ledger_entry_add(t, "cpu_time_billed_to_others", "sched", "ns");
	task_ledgers.physical_writes = ledger_entry_add(t, "physical_writes", "res", "bytes");
	task_ledgers.logical_writes = ledger_entry_add(t, "logical_writes", "res", "bytes");
	task_ledgers.energy_billed_to_me = ledger_entry_add(t, "energy_billed_to_me", "power", "nj");
	task_ledgers.energy_billed_to_others = ledger_entry_add(t, "energy_billed_to_others", "power", "nj");

	if ((task_ledgers.cpu_time < 0) ||
	    (task_ledgers.tkm_private < 0) ||
	    (task_ledgers.tkm_shared < 0) ||
	    (task_ledgers.phys_mem < 0) ||
	    (task_ledgers.wired_mem < 0) ||
	    (task_ledgers.internal < 0) ||
	    (task_ledgers.iokit_mapped < 0) ||
	    (task_ledgers.alternate_accounting < 0) ||
	    (task_ledgers.alternate_accounting_compressed < 0) ||
	    (task_ledgers.page_table < 0) ||
	    (task_ledgers.phys_footprint < 0) ||
	    (task_ledgers.internal_compressed < 0) ||
	    (task_ledgers.purgeable_volatile < 0) ||
	    (task_ledgers.purgeable_nonvolatile < 0) ||
	    (task_ledgers.purgeable_volatile_compressed < 0) ||
	    (task_ledgers.purgeable_nonvolatile_compressed < 0) ||
	    (task_ledgers.network_volatile < 0) ||
	    (task_ledgers.network_nonvolatile < 0) ||
	    (task_ledgers.network_volatile_compressed < 0) ||
	    (task_ledgers.network_nonvolatile_compressed < 0) ||
	    (task_ledgers.platform_idle_wakeups < 0) ||
	    (task_ledgers.interrupt_wakeups < 0) ||
	    (task_ledgers.cpu_time_billed_to_me < 0) || (task_ledgers.cpu_time_billed_to_others < 0) ||
	    (task_ledgers.physical_writes < 0) ||
	    (task_ledgers.logical_writes < 0) ||
	    (task_ledgers.energy_billed_to_me < 0) ||
	    (task_ledgers.energy_billed_to_others < 0)
	    ) {
		panic("couldn't create entries for task ledger template");
	}

	ledger_track_credit_only(t, task_ledgers.phys_footprint);
	ledger_track_credit_only(t, task_ledgers.page_table);
	ledger_track_credit_only(t, task_ledgers.internal);
	ledger_track_credit_only(t, task_ledgers.internal_compressed);
	ledger_track_credit_only(t, task_ledgers.iokit_mapped);
	ledger_track_credit_only(t, task_ledgers.alternate_accounting);
	ledger_track_credit_only(t, task_ledgers.alternate_accounting_compressed);
	ledger_track_credit_only(t, task_ledgers.purgeable_volatile);
	ledger_track_credit_only(t, task_ledgers.purgeable_nonvolatile);
	ledger_track_credit_only(t, task_ledgers.purgeable_volatile_compressed);
	ledger_track_credit_only(t, task_ledgers.purgeable_nonvolatile_compressed);

	ledger_track_credit_only(t, task_ledgers.network_volatile);
	ledger_track_credit_only(t, task_ledgers.network_nonvolatile);
	ledger_track_credit_only(t, task_ledgers.network_volatile_compressed);
	ledger_track_credit_only(t, task_ledgers.network_nonvolatile_compressed);

	ledger_track_maximum(t, task_ledgers.phys_footprint, 60);
#if MACH_ASSERT
	if (pmap_ledgers_panic) {
		ledger_panic_on_negative(t, task_ledgers.phys_footprint);
		ledger_panic_on_negative(t, task_ledgers.page_table);
		ledger_panic_on_negative(t, task_ledgers.internal);
		ledger_panic_on_negative(t, task_ledgers.internal_compressed);
		ledger_panic_on_negative(t, task_ledgers.iokit_mapped);
		ledger_panic_on_negative(t, task_ledgers.alternate_accounting);
		ledger_panic_on_negative(t, task_ledgers.alternate_accounting_compressed);
		ledger_panic_on_negative(t, task_ledgers.purgeable_volatile);
		ledger_panic_on_negative(t, task_ledgers.purgeable_nonvolatile);
		ledger_panic_on_negative(t, task_ledgers.purgeable_volatile_compressed);
		ledger_panic_on_negative(t, task_ledgers.purgeable_nonvolatile_compressed);

		ledger_panic_on_negative(t, task_ledgers.network_volatile);
		ledger_panic_on_negative(t, task_ledgers.network_nonvolatile);
		ledger_panic_on_negative(t, task_ledgers.network_volatile_compressed);
		ledger_panic_on_negative(t, task_ledgers.network_nonvolatile_compressed);
	}
#endif /* MACH_ASSERT */

#if CONFIG_MEMORYSTATUS
	ledger_set_callback(t, task_ledgers.phys_footprint, task_footprint_exceeded, NULL, NULL);
#endif /* CONFIG_MEMORYSTATUS */

	ledger_set_callback(t, task_ledgers.interrupt_wakeups,
		task_wakeups_rate_exceeded, NULL, NULL);
	ledger_set_callback(t, task_ledgers.physical_writes, task_io_rate_exceeded, (void *)FLAVOR_IO_PHYSICAL_WRITES, NULL);
	ledger_set_callback(t, task_ledgers.logical_writes, task_io_rate_exceeded, (void *)FLAVOR_IO_LOGICAL_WRITES, NULL);

	ledger_template_complete(t);
	task_ledger_template = t;
}