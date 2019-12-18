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
struct vcpu_svm {TYPE_3__* vmcb; } ;
struct TYPE_4__ {int shadow_efer; unsigned long cr0; } ;
struct kvm_vcpu {int /*<<< orphan*/  fpu_active; TYPE_1__ arch; } ;
struct TYPE_5__ {int efer; unsigned long cr0; } ;
struct TYPE_6__ {TYPE_2__ save; } ;

/* Variables and functions */
 int EFER_LMA ; 
 int EFER_LME ; 
 int /*<<< orphan*/  VMCB_CR ; 
 unsigned long X86_CR0_CD ; 
 unsigned long X86_CR0_NW ; 
 unsigned long X86_CR0_PG ; 
 unsigned long X86_CR0_TS ; 
 unsigned long X86_CR0_WP ; 
 scalar_t__ is_paging (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  mark_dirty (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ npt_enabled ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void svm_set_cr0(struct kvm_vcpu *vcpu, unsigned long cr0)
{
	struct vcpu_svm *svm = to_svm(vcpu);

#ifdef CONFIG_X86_64
	if (vcpu->arch.shadow_efer & EFER_LME) {
		if (!is_paging(vcpu) && (cr0 & X86_CR0_PG)) {
			vcpu->arch.shadow_efer |= EFER_LMA;
			svm->vmcb->save.efer |= EFER_LMA | EFER_LME;
		}

		if (is_paging(vcpu) && !(cr0 & X86_CR0_PG)) {
			vcpu->arch.shadow_efer &= ~EFER_LMA;
			svm->vmcb->save.efer &= ~(EFER_LMA | EFER_LME);
		}
	}
#endif
	if (npt_enabled)
		goto set;

	vcpu->arch.cr0 = cr0;
	cr0 |= X86_CR0_PG | X86_CR0_WP;

	if (!vcpu->fpu_active)
		cr0 |= X86_CR0_TS;
set:
	/*
	 * re-enable caching here because the QEMU bios
	 * does not do it - this results in some delay at
	 * reboot
	 */
	cr0 &= ~(X86_CR0_CD | X86_CR0_NW);
	svm->vmcb->save.cr0 = cr0;
	mark_dirty(to_svm(vcpu)->vmcb, VMCB_CR);
}