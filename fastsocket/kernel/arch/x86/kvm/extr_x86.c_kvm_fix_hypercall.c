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
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* patch_hypercall ) (struct kvm_vcpu*,char*) ;} ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ X86EMUL_CONTINUE ; 
 scalar_t__ emulator_write_emulated (unsigned long,char*,int,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mmu_zap_all (int /*<<< orphan*/ ) ; 
 unsigned long kvm_rip_read (struct kvm_vcpu*) ; 
 TYPE_1__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,char*) ; 

int kvm_fix_hypercall(struct kvm_vcpu *vcpu)
{
	char instruction[3];
	int ret = 0;
	unsigned long rip = kvm_rip_read(vcpu);


	/*
	 * Blow out the MMU to ensure that no other VCPU has an active mapping
	 * to ensure that the updated hypercall appears atomically across all
	 * VCPUs.
	 */
	kvm_mmu_zap_all(vcpu->kvm);

	kvm_x86_ops->patch_hypercall(vcpu, instruction);
	if (emulator_write_emulated(rip, instruction, 3, vcpu)
	    != X86EMUL_CONTINUE)
		ret = -EFAULT;

	return ret;
}