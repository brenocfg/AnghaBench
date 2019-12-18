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
 int /*<<< orphan*/  __vcpu_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __vmx_load_host_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_cpu_vmxoff () ; 
 int /*<<< orphan*/  to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmm_exclusive ; 

__attribute__((used)) static void vmx_vcpu_put(struct kvm_vcpu *vcpu)
{
	__vmx_load_host_state(to_vmx(vcpu));
	if (!vmm_exclusive) {
		__vcpu_clear(to_vmx(vcpu));
		kvm_cpu_vmxoff();
	}
}