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
struct vcpu_svm {int /*<<< orphan*/  vcpu; TYPE_2__* vmcb; } ;
struct TYPE_3__ {int exit_info_1; int exit_code; } ;
struct TYPE_4__ {TYPE_1__ control; } ;

/* Variables and functions */
 int SVM_EXITINFO_REG_MASK ; 
 int SVM_EXIT_READ_DR0 ; 
 int /*<<< orphan*/  SVM_FEATURE_DECODE_ASSIST ; 
 int emulate_on_interception (struct vcpu_svm*) ; 
 unsigned long kvm_register_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kvm_register_write (int /*<<< orphan*/ *,int,unsigned long) ; 
 int /*<<< orphan*/  skip_emulated_instruction (int /*<<< orphan*/ *) ; 
 unsigned long svm_get_dr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svm_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svm_set_dr (int /*<<< orphan*/ *,int,unsigned long,int*) ; 

__attribute__((used)) static int dr_interception(struct vcpu_svm *svm)
{
	int reg, dr;
	unsigned long val;
	int err = 0;

	if (!svm_has(SVM_FEATURE_DECODE_ASSIST))
		return emulate_on_interception(svm);

	reg = svm->vmcb->control.exit_info_1 & SVM_EXITINFO_REG_MASK;
	dr = svm->vmcb->control.exit_code - SVM_EXIT_READ_DR0;

	if (dr >= 16) { /* mov to DRn */
		val = kvm_register_read(&svm->vcpu, reg);
		svm_set_dr(&svm->vcpu, dr - 16, val, &err);
	} else {
		val = svm_get_dr(&svm->vcpu, dr);
		kvm_register_write(&svm->vcpu, reg, val);
	}
	skip_emulated_instruction(&svm->vcpu);

	return 1;
}