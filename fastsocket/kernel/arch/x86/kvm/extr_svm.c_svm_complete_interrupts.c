#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_10__ {int hflags; int nmi_injected; } ;
struct TYPE_13__ {TYPE_1__ arch; } ;
struct vcpu_svm {scalar_t__ nmi_iret_rip; TYPE_4__ vcpu; TYPE_3__* vmcb; } ;
struct TYPE_11__ {int exit_int_info; int exit_int_info_err; } ;
struct TYPE_12__ {TYPE_2__ control; } ;

/* Variables and functions */
 int HF_IRET_MASK ; 
 int HF_NMI_MASK ; 
#define  SVM_EXITINTINFO_TYPE_EXEPT 130 
#define  SVM_EXITINTINFO_TYPE_INTR 129 
 int SVM_EXITINTINFO_TYPE_MASK ; 
#define  SVM_EXITINTINFO_TYPE_NMI 128 
 int SVM_EXITINTINFO_VALID ; 
 int SVM_EXITINTINFO_VALID_ERR ; 
 int SVM_EXITINTINFO_VEC_MASK ; 
 int /*<<< orphan*/  is_nested (struct vcpu_svm*) ; 
 int /*<<< orphan*/  kvm_clear_exception_queue (TYPE_4__*) ; 
 int /*<<< orphan*/  kvm_clear_interrupt_queue (TYPE_4__*) ; 
 int /*<<< orphan*/  kvm_exception_is_soft (int) ; 
 int /*<<< orphan*/  kvm_queue_exception (TYPE_4__*,int) ; 
 int /*<<< orphan*/  kvm_queue_exception_e (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  kvm_queue_interrupt (TYPE_4__*,int,int) ; 
 scalar_t__ kvm_rip_read (TYPE_4__*) ; 

__attribute__((used)) static void svm_complete_interrupts(struct vcpu_svm *svm)
{
	u8 vector;
	int type;
	u32 exitintinfo = svm->vmcb->control.exit_int_info;

	/*
	 * If we've made progress since setting HF_IRET_MASK, we've
	 * executed an IRET and can allow NMI injection.
	 */
	if ((svm->vcpu.arch.hflags & HF_IRET_MASK)
	    && kvm_rip_read(&svm->vcpu) != svm->nmi_iret_rip)
		svm->vcpu.arch.hflags &= ~(HF_NMI_MASK | HF_IRET_MASK);

	svm->vcpu.arch.nmi_injected = false;
	kvm_clear_exception_queue(&svm->vcpu);
	kvm_clear_interrupt_queue(&svm->vcpu);

	if (!(exitintinfo & SVM_EXITINTINFO_VALID))
		return;

	vector = exitintinfo & SVM_EXITINTINFO_VEC_MASK;
	type = exitintinfo & SVM_EXITINTINFO_TYPE_MASK;

	switch (type) {
	case SVM_EXITINTINFO_TYPE_NMI:
		svm->vcpu.arch.nmi_injected = true;
		break;
	case SVM_EXITINTINFO_TYPE_EXEPT:
		/* In case of software exception do not reinject an exception
		   vector, but re-execute and instruction instead */
		if (is_nested(svm))
			break;
		if (kvm_exception_is_soft(vector))
			break;
		if (exitintinfo & SVM_EXITINTINFO_VALID_ERR) {
			u32 err = svm->vmcb->control.exit_int_info_err;
			kvm_queue_exception_e(&svm->vcpu, vector, err);

		} else
			kvm_queue_exception(&svm->vcpu, vector);
		break;
	case SVM_EXITINTINFO_TYPE_INTR:
		kvm_queue_interrupt(&svm->vcpu, vector, false);
		break;
	default:
		break;
	}
}