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
struct TYPE_3__ {int /*<<< orphan*/  last_guest_tsc; int /*<<< orphan*/  last_host_tsc; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* vcpu_put ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_TSC ; 
 int /*<<< orphan*/  kvm_get_msr (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_put_guest_fpu (struct kvm_vcpu*) ; 
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  native_read_tsc () ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*) ; 

void kvm_arch_vcpu_put(struct kvm_vcpu *vcpu)
{
	kvm_put_guest_fpu(vcpu);
	vcpu->arch.last_host_tsc = native_read_tsc();
	kvm_get_msr(vcpu, MSR_IA32_TSC, &vcpu->arch.last_guest_tsc);
	kvm_x86_ops->vcpu_put(vcpu);
}