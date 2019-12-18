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
typedef  int u32 ;
struct vcpu_svm {TYPE_2__* vmcb; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_3__ {int int_state; } ;
struct TYPE_4__ {TYPE_1__ control; } ;

/* Variables and functions */
 int SVM_INTERRUPT_SHADOW_MASK ; 
 int X86_SHADOW_INT_MOV_SS ; 
 int X86_SHADOW_INT_STI ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static u32 svm_get_interrupt_shadow(struct kvm_vcpu *vcpu, int mask)
{
	struct vcpu_svm *svm = to_svm(vcpu);
	u32 ret = 0;

	if (svm->vmcb->control.int_state & SVM_INTERRUPT_SHADOW_MASK)
		ret |= X86_SHADOW_INT_STI | X86_SHADOW_INT_MOV_SS;
	return ret & mask;
}