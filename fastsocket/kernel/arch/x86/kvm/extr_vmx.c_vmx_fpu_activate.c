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
struct TYPE_2__ {int /*<<< orphan*/  cr0_guest_owned_bits; } ;
struct kvm_vcpu {int fpu_active; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR0_GUEST_HOST_MASK ; 
 int /*<<< orphan*/  GUEST_CR0 ; 
 int /*<<< orphan*/  X86_CR0_TS ; 
 scalar_t__ kvm_read_cr0_bits (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_exception_bitmap (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmcs_clear_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmx_fpu_activate(struct kvm_vcpu *vcpu)
{
	if (vcpu->fpu_active)
		return;
	vcpu->fpu_active = 1;
	vmcs_clear_bits(GUEST_CR0, X86_CR0_TS);
	if (kvm_read_cr0_bits(vcpu, X86_CR0_TS))
		vmcs_set_bits(GUEST_CR0, X86_CR0_TS);
	update_exception_bitmap(vcpu);
	vcpu->arch.cr0_guest_owned_bits = X86_CR0_TS;
	vmcs_writel(CR0_GUEST_HOST_MASK, ~vcpu->arch.cr0_guest_owned_bits);
}