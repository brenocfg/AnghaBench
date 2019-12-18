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
struct TYPE_4__ {scalar_t__ singlestep; } ;
struct kvm_vcpu {int guest_debug; TYPE_1__ arch; } ;
struct TYPE_5__ {int intercept_exceptions; } ;
struct TYPE_6__ {TYPE_2__ control; } ;

/* Variables and functions */
 int BP_VECTOR ; 
 int DB_VECTOR ; 
 int KVM_GUESTDBG_ENABLE ; 
 int KVM_GUESTDBG_SINGLESTEP ; 
 int KVM_GUESTDBG_USE_HW_BP ; 
 int KVM_GUESTDBG_USE_SW_BP ; 
 int /*<<< orphan*/  VMCB_INTERCEPTS ; 
 int /*<<< orphan*/  mark_dirty (TYPE_3__*,int /*<<< orphan*/ ) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void update_db_intercept(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);

	svm->vmcb->control.intercept_exceptions &=
		~((1 << DB_VECTOR) | (1 << BP_VECTOR));

	if (vcpu->arch.singlestep)
		svm->vmcb->control.intercept_exceptions |= (1 << DB_VECTOR);

	if (vcpu->guest_debug & KVM_GUESTDBG_ENABLE) {
		if (vcpu->guest_debug &
		    (KVM_GUESTDBG_SINGLESTEP | KVM_GUESTDBG_USE_HW_BP))
			svm->vmcb->control.intercept_exceptions |=
				1 << DB_VECTOR;
		if (vcpu->guest_debug & KVM_GUESTDBG_USE_SW_BP)
			svm->vmcb->control.intercept_exceptions |=
				1 << BP_VECTOR;
	} else
		vcpu->guest_debug = 0;

	mark_dirty(svm->vmcb, VMCB_INTERCEPTS);
}