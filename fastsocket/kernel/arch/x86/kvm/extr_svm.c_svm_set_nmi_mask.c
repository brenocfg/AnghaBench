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
struct TYPE_7__ {int /*<<< orphan*/  hflags; } ;
struct TYPE_6__ {TYPE_3__ arch; } ;
struct vcpu_svm {TYPE_4__* vmcb; TYPE_2__ vcpu; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_5__ {unsigned long intercept; } ;
struct TYPE_8__ {TYPE_1__ control; } ;

/* Variables and functions */
 int /*<<< orphan*/  HF_NMI_MASK ; 
 unsigned long INTERCEPT_IRET ; 
 int /*<<< orphan*/  VMCB_INTERCEPTS ; 
 int /*<<< orphan*/  mark_dirty (TYPE_4__*,int /*<<< orphan*/ ) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void svm_set_nmi_mask(struct kvm_vcpu *vcpu, bool masked)
{
	struct vcpu_svm *svm = to_svm(vcpu);

	if (masked) {
		svm->vcpu.arch.hflags |= HF_NMI_MASK;
		svm->vmcb->control.intercept |= (1UL << INTERCEPT_IRET);
	} else {
		svm->vcpu.arch.hflags &= ~HF_NMI_MASK;
		svm->vmcb->control.intercept &= ~(1UL << INTERCEPT_IRET);
	}
	mark_dirty(svm->vmcb, VMCB_INTERCEPTS);
}