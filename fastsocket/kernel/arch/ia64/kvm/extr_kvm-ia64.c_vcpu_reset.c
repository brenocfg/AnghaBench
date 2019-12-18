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
struct TYPE_2__ {scalar_t__ launched; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int kvm_arch_vcpu_init (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_arch_vcpu_uninit (struct kvm_vcpu*) ; 
 int kvm_insert_vmm_mapping (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_purge_vmm_mapping (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  local_irq_restore (long) ; 
 int /*<<< orphan*/  local_irq_save (long) ; 

__attribute__((used)) static int vcpu_reset(struct kvm_vcpu *vcpu)
{
	int r;
	long psr;
	local_irq_save(psr);
	r = kvm_insert_vmm_mapping(vcpu);
	local_irq_restore(psr);
	if (r)
		goto fail;

	vcpu->arch.launched = 0;
	kvm_arch_vcpu_uninit(vcpu);
	r = kvm_arch_vcpu_init(vcpu);
	if (r)
		goto fail;

	kvm_purge_vmm_mapping(vcpu);
	r = 0;
fail:
	return r;
}