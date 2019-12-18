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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_5__ {int def_type; int enabled; TYPE_1__* var_ranges; int /*<<< orphan*/  fixed_ranges; } ;
struct TYPE_6__ {int pat; TYPE_2__ mtrr_state; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  mask_lo; int /*<<< orphan*/  base_lo; } ;

/* Variables and functions */
 scalar_t__ MSR_IA32_CR_PAT ; 
 scalar_t__ MSR_MTRRdefType ; 
 scalar_t__ MSR_MTRRfix16K_80000 ; 
 scalar_t__ MSR_MTRRfix16K_A0000 ; 
 scalar_t__ MSR_MTRRfix4K_C0000 ; 
 scalar_t__ MSR_MTRRfix4K_F8000 ; 
 scalar_t__ MSR_MTRRfix64K_00000 ; 
 int /*<<< orphan*/  kvm_mmu_reset_context (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  mtrr_valid (struct kvm_vcpu*,scalar_t__,int) ; 

__attribute__((used)) static int set_msr_mtrr(struct kvm_vcpu *vcpu, u32 msr, u64 data)
{
	u64 *p = (u64 *)&vcpu->arch.mtrr_state.fixed_ranges;

	if (!mtrr_valid(vcpu, msr, data))
		return 1;

	if (msr == MSR_MTRRdefType) {
		vcpu->arch.mtrr_state.def_type = data;
		vcpu->arch.mtrr_state.enabled = (data & 0xc00) >> 10;
	} else if (msr == MSR_MTRRfix64K_00000)
		p[0] = data;
	else if (msr == MSR_MTRRfix16K_80000 || msr == MSR_MTRRfix16K_A0000)
		p[1 + msr - MSR_MTRRfix16K_80000] = data;
	else if (msr >= MSR_MTRRfix4K_C0000 && msr <= MSR_MTRRfix4K_F8000)
		p[3 + msr - MSR_MTRRfix4K_C0000] = data;
	else if (msr == MSR_IA32_CR_PAT)
		vcpu->arch.pat = data;
	else {	/* Variable MTRRs */
		int idx, is_mtrr_mask;
		u64 *pt;

		idx = (msr - 0x200) / 2;
		is_mtrr_mask = msr - 0x200 - 2 * idx;
		if (!is_mtrr_mask)
			pt =
			  (u64 *)&vcpu->arch.mtrr_state.var_ranges[idx].base_lo;
		else
			pt =
			  (u64 *)&vcpu->arch.mtrr_state.var_ranges[idx].mask_lo;
		*pt = data;
	}

	kvm_mmu_reset_context(vcpu);
	return 0;
}