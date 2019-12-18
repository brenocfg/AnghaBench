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
struct TYPE_2__ {int /*<<< orphan*/  exit_data; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_ia64_vcpu_stack {int /*<<< orphan*/ * stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct kvm_vcpu*,int /*<<< orphan*/ *,int) ; 

int kvm_arch_vcpu_ioctl_set_stack(struct kvm_vcpu *vcpu,
				  struct kvm_ia64_vcpu_stack *stack)
{
	memcpy(vcpu + 1, &stack->stack[0] + sizeof(struct kvm_vcpu),
	       sizeof(struct kvm_ia64_vcpu_stack) - sizeof(struct kvm_vcpu));

	vcpu->arch.exit_data = ((struct kvm_vcpu *)stack)->arch.exit_data;
	return 0;
}