#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int singlestep; } ;
struct TYPE_15__ {int guest_debug; TYPE_1__ arch; struct kvm_run* run; } ;
struct vcpu_svm {TYPE_4__* vmcb; TYPE_7__ vcpu; } ;
struct TYPE_13__ {int /*<<< orphan*/  exception; scalar_t__ pc; } ;
struct TYPE_14__ {TYPE_5__ arch; } ;
struct kvm_run {TYPE_6__ debug; int /*<<< orphan*/  exit_reason; } ;
struct TYPE_10__ {scalar_t__ base; } ;
struct TYPE_11__ {int rflags; scalar_t__ rip; TYPE_2__ cs; } ;
struct TYPE_12__ {TYPE_3__ save; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB_VECTOR ; 
 int /*<<< orphan*/  KVM_EXIT_DEBUG ; 
 int KVM_GUESTDBG_SINGLESTEP ; 
 int KVM_GUESTDBG_USE_HW_BP ; 
 int X86_EFLAGS_RF ; 
 int X86_EFLAGS_TF ; 
 int /*<<< orphan*/  kvm_queue_exception (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_db_intercept (TYPE_7__*) ; 

__attribute__((used)) static int db_interception(struct vcpu_svm *svm)
{
	struct kvm_run *kvm_run = svm->vcpu.run;

	if (!(svm->vcpu.guest_debug &
	      (KVM_GUESTDBG_SINGLESTEP | KVM_GUESTDBG_USE_HW_BP)) &&
		!svm->vcpu.arch.singlestep) {
		kvm_queue_exception(&svm->vcpu, DB_VECTOR);
		return 1;
	}

	if (svm->vcpu.arch.singlestep) {
		svm->vcpu.arch.singlestep = false;
		if (!(svm->vcpu.guest_debug & KVM_GUESTDBG_SINGLESTEP))
			svm->vmcb->save.rflags &=
				~(X86_EFLAGS_TF | X86_EFLAGS_RF);
		update_db_intercept(&svm->vcpu);
	}

	if (svm->vcpu.guest_debug &
	    (KVM_GUESTDBG_SINGLESTEP | KVM_GUESTDBG_USE_HW_BP)){
		kvm_run->exit_reason = KVM_EXIT_DEBUG;
		kvm_run->debug.arch.pc =
			svm->vmcb->save.cs.base + svm->vmcb->save.rip;
		kvm_run->debug.arch.exception = DB_VECTOR;
		return 0;
	}

	return 1;
}