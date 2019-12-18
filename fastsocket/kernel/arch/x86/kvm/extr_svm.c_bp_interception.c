#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct kvm_run* run; } ;
struct vcpu_svm {TYPE_5__* vmcb; TYPE_1__ vcpu; } ;
struct TYPE_8__ {int /*<<< orphan*/  exception; scalar_t__ pc; } ;
struct TYPE_9__ {TYPE_2__ arch; } ;
struct kvm_run {TYPE_3__ debug; int /*<<< orphan*/  exit_reason; } ;
struct TYPE_10__ {scalar_t__ base; } ;
struct TYPE_12__ {scalar_t__ rip; TYPE_4__ cs; } ;
struct TYPE_11__ {TYPE_6__ save; } ;

/* Variables and functions */
 int /*<<< orphan*/  BP_VECTOR ; 
 int /*<<< orphan*/  KVM_EXIT_DEBUG ; 

__attribute__((used)) static int bp_interception(struct vcpu_svm *svm)
{
	struct kvm_run *kvm_run = svm->vcpu.run;

	kvm_run->exit_reason = KVM_EXIT_DEBUG;
	kvm_run->debug.arch.pc = svm->vmcb->save.cs.base + svm->vmcb->save.rip;
	kvm_run->debug.arch.exception = BP_VECTOR;
	return 0;
}