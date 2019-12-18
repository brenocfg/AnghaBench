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
struct kvmppc_vcpu_e500 {int* guest_tlb_size; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _tlbil_all () ; 
 int /*<<< orphan*/  kvmppc_e500_shadow_release (struct kvmppc_vcpu_e500*,int,int) ; 
 struct kvmppc_vcpu_e500* to_e500 (struct kvm_vcpu*) ; 

void kvmppc_mmu_destroy(struct kvm_vcpu *vcpu)
{
	struct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	int tlbsel, i;

	for (tlbsel = 0; tlbsel < 2; tlbsel++)
		for (i = 0; i < vcpu_e500->guest_tlb_size[tlbsel]; i++)
			kvmppc_e500_shadow_release(vcpu_e500, tlbsel, i);

	/* discard all guest mapping */
	_tlbil_all();
}