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
struct perf_kvm_stat {char const* file_name; int trace_vcpu; char* report_event; char* sort_key; char* exit_reasons_isa; int /*<<< orphan*/  exit_reasons_size; int /*<<< orphan*/  exit_reasons; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int cmd_stat (int,char const**,int /*<<< orphan*/ *) ; 
 int kvm_events_record (struct perf_kvm_stat*,int,char const**) ; 
 int kvm_events_report (struct perf_kvm_stat*,int,char const**) ; 
 int /*<<< orphan*/  print_kvm_stat_usage () ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  svm_exit_reasons ; 

__attribute__((used)) static int kvm_cmd_stat(const char *file_name, int argc, const char **argv)
{
	struct perf_kvm_stat kvm = {
		.file_name = file_name,

		.trace_vcpu	= -1,
		.report_event	= "vmexit",
		.sort_key	= "sample",

		.exit_reasons = svm_exit_reasons,
		.exit_reasons_size = ARRAY_SIZE(svm_exit_reasons),
		.exit_reasons_isa = "SVM",
	};

	if (argc == 1) {
		print_kvm_stat_usage();
		goto perf_stat;
	}

	if (!strncmp(argv[1], "rec", 3))
		return kvm_events_record(&kvm, argc - 1, argv + 1);

	if (!strncmp(argv[1], "rep", 3))
		return kvm_events_report(&kvm, argc - 1 , argv + 1);

perf_stat:
	return cmd_stat(argc, argv, NULL);
}