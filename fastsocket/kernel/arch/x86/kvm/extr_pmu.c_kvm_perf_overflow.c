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
struct pt_regs {int dummy; } ;
struct perf_sample_data {int dummy; } ;
struct perf_event {struct kvm_pmc* overflow_handler_context; } ;
struct kvm_pmu {int /*<<< orphan*/  global_status; } ;
struct kvm_pmc {int /*<<< orphan*/  idx; TYPE_2__* vcpu; } ;
struct TYPE_3__ {struct kvm_pmu pmu; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void kvm_perf_overflow(struct perf_event *perf_event,
			      struct perf_sample_data *data,
			      struct pt_regs *regs)
{
	struct kvm_pmc *pmc = perf_event->overflow_handler_context;
	struct kvm_pmu *pmu = &pmc->vcpu->arch.pmu;
	__set_bit(pmc->idx, (unsigned long *)&pmu->global_status);
}