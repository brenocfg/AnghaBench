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
struct notifier_block {int dummy; } ;
struct TYPE_2__ {scalar_t__ need_hotplug_init; } ;
struct acpi_processor {TYPE_1__ flags; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 unsigned long CPU_DEAD ; 
 unsigned long CPU_ONLINE ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  WARN (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_processor_cst_has_changed (struct acpi_processor*) ; 
 int /*<<< orphan*/  acpi_processor_ppc_has_changed (struct acpi_processor*) ; 
 int /*<<< orphan*/  acpi_processor_reevaluate_tstate (struct acpi_processor*,unsigned long) ; 
 int /*<<< orphan*/  acpi_processor_start (struct acpi_processor*) ; 
 int /*<<< orphan*/  acpi_processor_tstate_has_changed (struct acpi_processor*) ; 
 struct acpi_processor* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  processors ; 

__attribute__((used)) static int acpi_cpu_soft_notify(struct notifier_block *nfb,
		unsigned long action, void *hcpu)
{
	unsigned int cpu = (unsigned long)hcpu;
	struct acpi_processor *pr = per_cpu(processors, cpu);

	if (action == CPU_ONLINE && pr) {
		/* CPU got physically hotplugged and onlined the first time:
		 * Initialize missing things
		 */
		if (pr->flags.need_hotplug_init) {
			pr_info("Will online and init hotplugged CPU: %d\n",
				pr->id);
			WARN(acpi_processor_start(pr), "Failed to start CPU:"
				" %d\n", pr->id);
			pr->flags.need_hotplug_init = 0;
		/* Normal CPU soft online event */
		} else {
			acpi_processor_ppc_has_changed(pr);
			acpi_processor_cst_has_changed(pr);
			acpi_processor_reevaluate_tstate(pr, action);
			acpi_processor_tstate_has_changed(pr);
		}
	}
	if (action == CPU_DEAD && pr) {
		/* invalidate the flag.throttling after one CPU is offline */
		acpi_processor_reevaluate_tstate(pr, action);
	}

	return NOTIFY_OK;
}