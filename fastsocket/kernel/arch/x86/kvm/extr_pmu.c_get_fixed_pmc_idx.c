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
struct kvm_pmu {int dummy; } ;
struct kvm_pmc {int dummy; } ;

/* Variables and functions */
 scalar_t__ MSR_CORE_PERF_FIXED_CTR0 ; 
 struct kvm_pmc* get_fixed_pmc (struct kvm_pmu*,scalar_t__) ; 

__attribute__((used)) static inline struct kvm_pmc *get_fixed_pmc_idx(struct kvm_pmu *pmu, int idx)
{
	return get_fixed_pmc(pmu, MSR_CORE_PERF_FIXED_CTR0 + idx);
}