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
struct perf_kvm_stat {int trace_vcpu; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  init_kvm_event_record (struct perf_kvm_stat*) ; 
 int /*<<< orphan*/  print_result (struct perf_kvm_stat*) ; 
 int read_events (struct perf_kvm_stat*) ; 
 int /*<<< orphan*/  register_kvm_events_ops (struct perf_kvm_stat*) ; 
 int /*<<< orphan*/  select_key (struct perf_kvm_stat*) ; 
 int /*<<< orphan*/  setup_pager () ; 
 int /*<<< orphan*/  sort_result (struct perf_kvm_stat*) ; 
 int /*<<< orphan*/  verify_vcpu (int) ; 

__attribute__((used)) static int kvm_events_report_vcpu(struct perf_kvm_stat *kvm)
{
	int ret = -EINVAL;
	int vcpu = kvm->trace_vcpu;

	if (!verify_vcpu(vcpu))
		goto exit;

	if (!select_key(kvm))
		goto exit;

	if (!register_kvm_events_ops(kvm))
		goto exit;

	init_kvm_event_record(kvm);
	setup_pager();

	ret = read_events(kvm);
	if (ret)
		goto exit;

	sort_result(kvm);
	print_result(kvm);

exit:
	return ret;
}