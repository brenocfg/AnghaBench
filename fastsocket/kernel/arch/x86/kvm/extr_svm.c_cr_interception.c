#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {unsigned long cr0; unsigned long cr2; unsigned long cr3; unsigned long cr4; } ;
struct TYPE_17__ {TYPE_3__ arch; } ;
struct vcpu_svm {TYPE_4__ vcpu; TYPE_2__* vmcb; } ;
struct TYPE_14__ {int exit_info_1; int exit_code; } ;
struct TYPE_15__ {TYPE_1__ control; } ;

/* Variables and functions */
 int CR_VALID ; 
 int SVM_EXITINFO_REG_MASK ; 
 int SVM_EXIT_READ_CR0 ; 
 int /*<<< orphan*/  SVM_FEATURE_DECODE_ASSIST ; 
 int /*<<< orphan*/  UD_VECTOR ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int emulate_on_interception (struct vcpu_svm*) ; 
 unsigned long kvm_get_cr8 (TYPE_4__*) ; 
 int /*<<< orphan*/  kvm_inject_gp (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_queue_exception (TYPE_4__*,int /*<<< orphan*/ ) ; 
 unsigned long kvm_register_read (TYPE_4__*,int) ; 
 int /*<<< orphan*/  kvm_register_write (TYPE_4__*,int,unsigned long) ; 
 int kvm_set_cr0 (TYPE_4__*,unsigned long) ; 
 int kvm_set_cr3 (TYPE_4__*,unsigned long) ; 
 int kvm_set_cr4 (TYPE_4__*,unsigned long) ; 
 int kvm_set_cr8 (TYPE_4__*,unsigned long) ; 
 int /*<<< orphan*/  skip_emulated_instruction (TYPE_4__*) ; 
 int /*<<< orphan*/  svm_has (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int cr_interception(struct vcpu_svm *svm)
{
	int reg, cr;
	unsigned long val;
	int err;

	if (!svm_has(SVM_FEATURE_DECODE_ASSIST))
		return emulate_on_interception(svm);

	if (unlikely((svm->vmcb->control.exit_info_1 & CR_VALID) == 0))
		return emulate_on_interception(svm);

	reg = svm->vmcb->control.exit_info_1 & SVM_EXITINFO_REG_MASK;
	cr = svm->vmcb->control.exit_code - SVM_EXIT_READ_CR0;

	err = 0;
	if (cr >= 16) { /* mov to cr */
		cr -= 16;
		val = kvm_register_read(&svm->vcpu, reg);
		switch (cr) {
		case 0:
			err = kvm_set_cr0(&svm->vcpu, val);
			break;
		case 3:
			err = kvm_set_cr3(&svm->vcpu, val);
			break;
		case 4:
			err = kvm_set_cr4(&svm->vcpu, val);
			break;
		case 8:
			err = kvm_set_cr8(&svm->vcpu, val);
			break;
		default:
			WARN(1, "unhandled write to CR%d", cr);
			kvm_queue_exception(&svm->vcpu, UD_VECTOR);
			return 1;
		}
	} else { /* mov from cr */
		switch (cr) {
		case 0:
			val = svm->vcpu.arch.cr0;
			break;
		case 2:
			val = svm->vcpu.arch.cr2;
			break;
		case 3:
			val = svm->vcpu.arch.cr3;
			break;
		case 4:
			val = svm->vcpu.arch.cr4;
			break;
		case 8:
			val = kvm_get_cr8(&svm->vcpu);
			break;
		default:
			WARN(1, "unhandled read from CR%d", cr);
			kvm_queue_exception(&svm->vcpu, UD_VECTOR);
			return 1;
		}
		kvm_register_write(&svm->vcpu, reg, val);
	}
	if (err)
		kvm_inject_gp(&svm->vcpu, 0);
	else
		skip_emulated_instruction(&svm->vcpu);

	return 1;
}