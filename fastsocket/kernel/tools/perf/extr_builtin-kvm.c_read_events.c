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
struct perf_tool {int ordered_samples; int /*<<< orphan*/  comm; int /*<<< orphan*/  sample; } ;
struct perf_kvm_stat {char* exit_reasons_isa; struct perf_tool tool; int /*<<< orphan*/  session; int /*<<< orphan*/  exit_reasons_size; int /*<<< orphan*/  exit_reasons; int /*<<< orphan*/  file_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int get_cpu_isa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event__process_comm ; 
 int /*<<< orphan*/  perf_session__has_traces (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  perf_session__new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct perf_tool*) ; 
 int perf_session__process_events (int /*<<< orphan*/ ,struct perf_tool*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  process_sample_event ; 
 int /*<<< orphan*/  vmx_exit_reasons ; 

__attribute__((used)) static int read_events(struct perf_kvm_stat *kvm)
{
	int ret;

	struct perf_tool eops = {
		.sample			= process_sample_event,
		.comm			= perf_event__process_comm,
		.ordered_samples	= true,
	};

	kvm->tool = eops;
	kvm->session = perf_session__new(kvm->file_name, O_RDONLY, 0, false,
					 &kvm->tool);
	if (!kvm->session) {
		pr_err("Initializing perf session failed\n");
		return -EINVAL;
	}

	if (!perf_session__has_traces(kvm->session, "kvm record"))
		return -EINVAL;

	/*
	 * Do not use 'isa' recorded in kvm_exit tracepoint since it is not
	 * traced in the old kernel.
	 */
	ret = get_cpu_isa(kvm->session);

	if (ret < 0)
		return ret;

	if (ret == 1) {
		kvm->exit_reasons = vmx_exit_reasons;
		kvm->exit_reasons_size = ARRAY_SIZE(vmx_exit_reasons);
		kvm->exit_reasons_isa = "VMX";
	}

	return perf_session__process_events(kvm->session, &kvm->tool);
}