#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cr4_pge; } ;
struct TYPE_6__ {TYPE_1__ base_role; } ;
struct TYPE_7__ {int cr3; unsigned long cr4; TYPE_2__ mmu; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* set_cr4 ) (struct kvm_vcpu*,unsigned long) ;} ;

/* Variables and functions */
 unsigned long CR4_RESERVED_BITS ; 
 int X86_CR3_PCID_MASK ; 
 unsigned long X86_CR4_OSXSAVE ; 
 unsigned long X86_CR4_PAE ; 
 unsigned long X86_CR4_PCIDE ; 
 unsigned long X86_CR4_PGE ; 
 unsigned long X86_CR4_PSE ; 
 unsigned long X86_CR4_RDWRGSFS ; 
 unsigned long X86_CR4_SMEP ; 
 unsigned long X86_CR4_VMXE ; 
 int /*<<< orphan*/  guest_cpuid_has_fsgsbase (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  guest_cpuid_has_pcid (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  guest_cpuid_has_smep (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  guest_cpuid_has_xsave (struct kvm_vcpu*) ; 
 scalar_t__ is_long_mode (struct kvm_vcpu*) ; 
 scalar_t__ is_paging (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mmu_reset_context (struct kvm_vcpu*) ; 
 unsigned long kvm_read_cr4 (struct kvm_vcpu*) ; 
 TYPE_4__* kvm_x86_ops ; 
 int /*<<< orphan*/  load_pdptrs (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,unsigned long) ; 
 int /*<<< orphan*/  tdp_enabled ; 
 int /*<<< orphan*/  update_cpuid (struct kvm_vcpu*) ; 

int kvm_set_cr4(struct kvm_vcpu *vcpu, unsigned long cr4)
{
	unsigned long old_cr4 = kvm_read_cr4(vcpu);
	unsigned long pdptr_bits = X86_CR4_PGE | X86_CR4_PSE |
				   X86_CR4_PAE | X86_CR4_SMEP;
	if (cr4 & CR4_RESERVED_BITS)
		return 1;

	if (!guest_cpuid_has_xsave(vcpu) && (cr4 & X86_CR4_OSXSAVE))
		return 1;

	if (!guest_cpuid_has_smep(vcpu) && (cr4 & X86_CR4_SMEP))
		return 1;

	if (!guest_cpuid_has_fsgsbase(vcpu) && (cr4 & X86_CR4_RDWRGSFS))
		return 1;

	if (is_long_mode(vcpu)) {
		if (!(cr4 & X86_CR4_PAE))
			return 1;
	} else if (is_paging(vcpu) && (cr4 & X86_CR4_PAE)
		   && ((cr4 ^ old_cr4) & pdptr_bits)
		   && !load_pdptrs(vcpu, vcpu->arch.cr3))
		return 1;

	if ((cr4 & X86_CR4_PCIDE) && !(old_cr4 & X86_CR4_PCIDE)) {
		if (!guest_cpuid_has_pcid(vcpu))
			return 1;

		/* PCID can not be enabled when cr3[11:0]!=000H or EFER.LMA=0 */
		if ((vcpu->arch.cr3 & X86_CR3_PCID_MASK) || !is_long_mode(vcpu))
			return 1;
	}

	if (cr4 & X86_CR4_VMXE)
		return 1;
	kvm_x86_ops->set_cr4(vcpu, cr4);
	vcpu->arch.cr4 = cr4;
	vcpu->arch.mmu.base_role.cr4_pge = (cr4 & X86_CR4_PGE) && !tdp_enabled;
	kvm_mmu_reset_context(vcpu);

	if ((cr4 ^ old_cr4) & X86_CR4_OSXSAVE)
		update_cpuid(vcpu);

	return 0;
}