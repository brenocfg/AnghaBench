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
struct perf_kvm_stat {int /*<<< orphan*/  sort_key; int /*<<< orphan*/  trace_vcpu; int /*<<< orphan*/  report_event; } ;
struct option {int dummy; } ;

/* Variables and functions */
 struct option const OPT_END () ; 
 struct option const OPT_INTEGER (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*) ; 
 struct option const OPT_STRING (char,char*,int /*<<< orphan*/ *,char*,char*) ; 
 int kvm_events_report_vcpu (struct perf_kvm_stat*) ; 
 int parse_options (int,char const**,struct option const*,char const* const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symbol__init () ; 
 int /*<<< orphan*/  usage_with_options (char const* const*,struct option const*) ; 

__attribute__((used)) static int
kvm_events_report(struct perf_kvm_stat *kvm, int argc, const char **argv)
{
	const struct option kvm_events_report_options[] = {
		OPT_STRING(0, "event", &kvm->report_event, "report event",
			    "event for reporting: vmexit, mmio, ioport"),
		OPT_INTEGER(0, "vcpu", &kvm->trace_vcpu,
			    "vcpu id to report"),
		OPT_STRING('k', "key", &kvm->sort_key, "sort-key",
			    "key for sorting: sample(sort by samples number)"
			    " time (sort by avg time)"),
		OPT_END()
	};

	const char * const kvm_events_report_usage[] = {
		"perf kvm stat report [<options>]",
		NULL
	};

	symbol__init();

	if (argc) {
		argc = parse_options(argc, argv,
				     kvm_events_report_options,
				     kvm_events_report_usage, 0);
		if (argc)
			usage_with_options(kvm_events_report_usage,
					   kvm_events_report_options);
	}

	return kvm_events_report_vcpu(kvm);
}