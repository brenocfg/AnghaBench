#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUEST_CS_SELECTOR ; 
 int /*<<< orphan*/  X86_CR0_PE ; 
 int X86_EFLAGS_VM ; 
 int /*<<< orphan*/  kvm_read_cr0_bits (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int vmcs_read16 (int /*<<< orphan*/ ) ; 
 int vmx_get_rflags (struct kvm_vcpu*) ; 

__attribute__((used)) static int vmx_get_cpl(struct kvm_vcpu *vcpu)
{
	if (!kvm_read_cr0_bits(vcpu, X86_CR0_PE)) /* if real mode */
		return 0;

	if (vmx_get_rflags(vcpu) & X86_EFLAGS_VM) /* if virtual 8086 */
		return 3;

	return vmcs_read16(GUEST_CS_SELECTOR) & 3;
}