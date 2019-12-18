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
struct kvm_vcpu {int fpu_active; } ;
struct TYPE_5__ {int /*<<< orphan*/  cr0; } ;
struct TYPE_4__ {int intercept_exceptions; } ;
struct TYPE_6__ {TYPE_2__ save; TYPE_1__ control; } ;

/* Variables and functions */
 int NM_VECTOR ; 
 int /*<<< orphan*/  VMCB_CR ; 
 int /*<<< orphan*/  VMCB_INTERCEPTS ; 
 int /*<<< orphan*/  X86_CR0_TS ; 
 int /*<<< orphan*/  mark_dirty (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ npt_enabled ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void svm_fpu_deactivate(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);

	if (npt_enabled) {
		/* hack: npt requires active fpu at this time */
		vcpu->fpu_active = 1;
		return;
	}

	svm->vmcb->control.intercept_exceptions |= 1 << NM_VECTOR;
	svm->vmcb->save.cr0 |= X86_CR0_TS;
	mark_dirty(svm->vmcb, VMCB_INTERCEPTS);
	mark_dirty(svm->vmcb, VMCB_CR);
}