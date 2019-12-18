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
struct TYPE_2__ {int /*<<< orphan*/  (* vcpu_free ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fx_free (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mmu_unload (struct kvm_vcpu*) ; 
 TYPE_1__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

void kvm_arch_vcpu_destroy(struct kvm_vcpu *vcpu)
{
	vcpu_load(vcpu);
	kvm_mmu_unload(vcpu);
	vcpu_put(vcpu);

	fx_free(vcpu);
	kvm_x86_ops->vcpu_free(vcpu);
}