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
struct kvm_pmu {int /*<<< orphan*/  fixed_ctr_ctrl; } ;
struct kvm_pmc {int /*<<< orphan*/  eventsel; } ;

/* Variables and functions */
 int X86_PMC_IDX_FIXED ; 
 int /*<<< orphan*/  fixed_en_pmi (int /*<<< orphan*/ ,int) ; 
 struct kvm_pmc* global_idx_to_pmc (struct kvm_pmu*,int) ; 
 scalar_t__ pmc_is_gp (struct kvm_pmc*) ; 
 int /*<<< orphan*/  reprogram_fixed_counter (struct kvm_pmc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reprogram_gp_counter (struct kvm_pmc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reprogram_idx(struct kvm_pmu *pmu, int idx)
{
	struct kvm_pmc *pmc = global_idx_to_pmc(pmu, idx);

	if (!pmc)
		return;

	if (pmc_is_gp(pmc))
		reprogram_gp_counter(pmc, pmc->eventsel);
	else {
		int fidx = idx - X86_PMC_IDX_FIXED;
		reprogram_fixed_counter(pmc,
				fixed_en_pmi(pmu->fixed_ctr_ctrl, fidx), fidx);
	}
}