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
struct vcpu_svm {TYPE_4__* vmcb; } ;
struct TYPE_5__ {int /*<<< orphan*/  nmi_injections; } ;
struct TYPE_6__ {int /*<<< orphan*/  hflags; } ;
struct kvm_vcpu {TYPE_1__ stat; TYPE_2__ arch; } ;
struct TYPE_7__ {int event_inj; unsigned long intercept; } ;
struct TYPE_8__ {TYPE_3__ control; } ;

/* Variables and functions */
 int /*<<< orphan*/  HF_NMI_MASK ; 
 unsigned long INTERCEPT_IRET ; 
 int SVM_EVTINJ_TYPE_NMI ; 
 int SVM_EVTINJ_VALID ; 
 int /*<<< orphan*/  VMCB_INTERCEPTS ; 
 int /*<<< orphan*/  mark_dirty (TYPE_4__*,int /*<<< orphan*/ ) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void svm_inject_nmi(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);

	svm->vmcb->control.event_inj = SVM_EVTINJ_VALID | SVM_EVTINJ_TYPE_NMI;
	vcpu->arch.hflags |= HF_NMI_MASK;
	svm->vmcb->control.intercept |= (1UL << INTERCEPT_IRET);
	mark_dirty(svm->vmcb, VMCB_INTERCEPTS);
	++vcpu->stat.nmi_injections;
}