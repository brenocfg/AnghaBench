#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct perf_event_attr {int size; int pinned; int exclude_idle; int exclude_host; int exclude_user; int exclude_kernel; unsigned int config; int sample_period; int /*<<< orphan*/  type; } ;
struct perf_event {int dummy; } ;
struct kvm_pmc {int counter; TYPE_3__* vcpu; int /*<<< orphan*/  idx; struct perf_event* perf_event; } ;
typedef  int /*<<< orphan*/  attr ;
struct TYPE_4__ {int /*<<< orphan*/  reprogram_pmi; } ;
struct TYPE_5__ {TYPE_1__ pmu; } ;
struct TYPE_6__ {TYPE_2__ arch; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct perf_event*) ; 
 int /*<<< orphan*/  PTR_ERR (struct perf_event*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  kvm_perf_overflow ; 
 int /*<<< orphan*/  kvm_perf_overflow_intr ; 
 struct perf_event* perf_event_create_kernel_counter (struct perf_event_attr*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kvm_pmc*) ; 
 int pmc_bitmask (struct kvm_pmc*) ; 
 int /*<<< orphan*/  printk_once (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reprogram_counter(struct kvm_pmc *pmc, u32 type,
		unsigned config, bool exclude_user, bool exclude_kernel,
		bool intr)
{
	struct perf_event *event;
	struct perf_event_attr attr = {
		.type = type,
		.size = sizeof(attr),
		.pinned = true,
		.exclude_idle = true,
		.exclude_host = 1,
		.exclude_user = exclude_user,
		.exclude_kernel = exclude_kernel,
		.config = config,
	};

	attr.sample_period = (-pmc->counter) & pmc_bitmask(pmc);

	event = perf_event_create_kernel_counter(&attr, -1, current,
						 intr ? kvm_perf_overflow_intr :
						 kvm_perf_overflow, pmc);
	if (IS_ERR(event)) {
		printk_once("kvm: pmu event creation failed %ld\n",
				PTR_ERR(event));
		return;
	}

	pmc->perf_event = event;
	clear_bit(pmc->idx, (unsigned long*)&pmc->vcpu->arch.pmu.reprogram_pmi);
}