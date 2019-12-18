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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_pmu {int /*<<< orphan*/ * counter_bitmask; } ;
struct kvm_pmc {size_t type; TYPE_2__* vcpu; } ;
struct TYPE_3__ {struct kvm_pmu pmu; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;

/* Variables and functions */

__attribute__((used)) static inline u64 pmc_bitmask(struct kvm_pmc *pmc)
{
	struct kvm_pmu *pmu = &pmc->vcpu->arch.pmu;

	return pmu->counter_bitmask[pmc->type];
}