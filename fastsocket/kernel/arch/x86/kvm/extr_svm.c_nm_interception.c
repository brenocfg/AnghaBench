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
struct TYPE_8__ {int fpu_active; } ;
struct vcpu_svm {TYPE_3__* vmcb; TYPE_4__ vcpu; } ;
struct TYPE_6__ {int /*<<< orphan*/  cr0; } ;
struct TYPE_5__ {int intercept_exceptions; } ;
struct TYPE_7__ {TYPE_2__ save; TYPE_1__ control; } ;

/* Variables and functions */
 int NM_VECTOR ; 
 int /*<<< orphan*/  VMCB_CR ; 
 int /*<<< orphan*/  VMCB_INTERCEPTS ; 
 int /*<<< orphan*/  X86_CR0_TS ; 
 int /*<<< orphan*/  kvm_read_cr0_bits (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_dirty (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nm_interception(struct vcpu_svm *svm)
{
	svm->vmcb->control.intercept_exceptions &= ~(1 << NM_VECTOR);
	if (!kvm_read_cr0_bits(&svm->vcpu, X86_CR0_TS))
		svm->vmcb->save.cr0 &= ~X86_CR0_TS;
	else
		svm->vmcb->save.cr0 |= X86_CR0_TS;
	svm->vcpu.fpu_active = 1;
	mark_dirty(svm->vmcb, VMCB_INTERCEPTS);
	mark_dirty(svm->vmcb, VMCB_CR);

	return 1;
}