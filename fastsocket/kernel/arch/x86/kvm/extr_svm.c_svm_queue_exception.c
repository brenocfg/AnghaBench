#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct vcpu_svm {TYPE_2__* vmcb; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_3__ {unsigned int event_inj; int /*<<< orphan*/  event_inj_err; } ;
struct TYPE_4__ {TYPE_1__ control; } ;

/* Variables and functions */
 unsigned int SVM_EVTINJ_TYPE_EXEPT ; 
 unsigned int SVM_EVTINJ_VALID ; 
 unsigned int SVM_EVTINJ_VALID_ERR ; 
 scalar_t__ nested_svm_check_exception (struct vcpu_svm*,unsigned int,int,int /*<<< orphan*/ ) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void svm_queue_exception(struct kvm_vcpu *vcpu, unsigned nr,
				bool has_error_code, u32 error_code)
{
	struct vcpu_svm *svm = to_svm(vcpu);

	/* If we are within a nested VM we'd better #VMEXIT and let the
	   guest handle the exception */
	if (nested_svm_check_exception(svm, nr, has_error_code, error_code))
		return;

	svm->vmcb->control.event_inj = nr
		| SVM_EVTINJ_VALID
		| (has_error_code ? SVM_EVTINJ_VALID_ERR : 0)
		| SVM_EVTINJ_TYPE_EXEPT;
	svm->vmcb->control.event_inj_err = error_code;
}