#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ root_level; scalar_t__ (* sync_page ) (struct kvm_vcpu*,struct kvm_mmu_page*) ;} ;
struct TYPE_6__ {TYPE_2__ mmu; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_3__ arch; } ;
struct TYPE_4__ {scalar_t__ glevels; } ;
struct kvm_mmu_page {int /*<<< orphan*/  gfn; TYPE_1__ role; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_flush_remote_tlbs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_mmu_flush_tlb (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mmu_zap_page (int /*<<< orphan*/ ,struct kvm_mmu_page*) ; 
 int /*<<< orphan*/  kvm_unlink_unsync_page (int /*<<< orphan*/ ,struct kvm_mmu_page*) ; 
 scalar_t__ rmap_write_protect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct kvm_vcpu*,struct kvm_mmu_page*) ; 
 int /*<<< orphan*/  trace_kvm_mmu_sync_page (struct kvm_mmu_page*) ; 

__attribute__((used)) static int kvm_sync_page(struct kvm_vcpu *vcpu, struct kvm_mmu_page *sp)
{
	if (sp->role.glevels != vcpu->arch.mmu.root_level) {
		kvm_mmu_zap_page(vcpu->kvm, sp);
		return 1;
	}

	trace_kvm_mmu_sync_page(sp);
	if (rmap_write_protect(vcpu->kvm, sp->gfn))
		kvm_flush_remote_tlbs(vcpu->kvm);
	kvm_unlink_unsync_page(vcpu->kvm, sp);
	if (vcpu->arch.mmu.sync_page(vcpu, sp)) {
		kvm_mmu_zap_page(vcpu->kvm, sp);
		return 1;
	}

	kvm_mmu_flush_tlb(vcpu);
	return 0;
}