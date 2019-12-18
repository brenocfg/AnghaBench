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
struct msr_data {int data; int host_initiated; int /*<<< orphan*/  index; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_TSC ; 
 int /*<<< orphan*/  kvm_write_tsc (struct kvm_vcpu*,struct msr_data*) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_postcreate(struct kvm_vcpu *vcpu)
{
	struct msr_data msr;

	vcpu_load(vcpu);
	msr.data = 0x0;
	msr.index = MSR_IA32_TSC;
	msr.host_initiated = true;
	kvm_write_tsc(vcpu, &msr);
	vcpu_put(vcpu);

	return 0;
}