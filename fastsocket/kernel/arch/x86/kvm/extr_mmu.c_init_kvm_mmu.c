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
struct TYPE_3__ {int /*<<< orphan*/  pfn; } ;
struct TYPE_4__ {TYPE_1__ update_pte; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  bad_pfn ; 
 int init_kvm_softmmu (struct kvm_vcpu*) ; 
 int init_kvm_tdp_mmu (struct kvm_vcpu*) ; 
 scalar_t__ tdp_enabled ; 

__attribute__((used)) static int init_kvm_mmu(struct kvm_vcpu *vcpu)
{
	vcpu->arch.update_pte.pfn = bad_pfn;

	if (tdp_enabled)
		return init_kvm_tdp_mmu(vcpu);
	else
		return init_kvm_softmmu(vcpu);
}