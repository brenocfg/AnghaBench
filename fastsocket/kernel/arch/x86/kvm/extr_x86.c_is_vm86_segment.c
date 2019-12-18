#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int (* get_rflags ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int VCPU_SREG_LDTR ; 
 int VCPU_SREG_TR ; 
 int X86_EFLAGS_VM ; 
 TYPE_1__* kvm_x86_ops ; 
 int stub1 (struct kvm_vcpu*) ; 

__attribute__((used)) static int is_vm86_segment(struct kvm_vcpu *vcpu, int seg)
{
	return (seg != VCPU_SREG_LDTR) &&
		(seg != VCPU_SREG_TR) &&
		(kvm_x86_ops->get_rflags(vcpu) & X86_EFLAGS_VM);
}