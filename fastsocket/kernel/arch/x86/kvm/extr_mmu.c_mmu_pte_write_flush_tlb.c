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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_flush_remote_tlbs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_mmu_flush_tlb (struct kvm_vcpu*) ; 
 scalar_t__ need_remote_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mmu_pte_write_flush_tlb(struct kvm_vcpu *vcpu, u64 old, u64 new)
{
	if (need_remote_flush(old, new))
		kvm_flush_remote_tlbs(vcpu->kvm);
	else
		kvm_mmu_flush_tlb(vcpu);
}