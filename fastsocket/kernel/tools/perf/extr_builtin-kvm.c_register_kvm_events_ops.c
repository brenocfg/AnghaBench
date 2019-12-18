#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct perf_kvm_stat {int /*<<< orphan*/  report_event; int /*<<< orphan*/ * events_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit_events ; 
 int /*<<< orphan*/  ioport_events ; 
 int /*<<< orphan*/  mmio_events ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool register_kvm_events_ops(struct perf_kvm_stat *kvm)
{
	bool ret = true;

	if (!strcmp(kvm->report_event, "vmexit"))
		kvm->events_ops = &exit_events;
	else if (!strcmp(kvm->report_event, "mmio"))
		kvm->events_ops = &mmio_events;
	else if (!strcmp(kvm->report_event, "ioport"))
		kvm->events_ops = &ioport_events;
	else {
		pr_err("Unknown report event:%s\n", kvm->report_event);
		ret = false;
	}

	return ret;
}