#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int root_hpa; scalar_t__ shadow_root_level; int* pae_root; } ;
struct TYPE_7__ {TYPE_2__ mmu; } ;
struct kvm_vcpu {TYPE_3__ arch; TYPE_4__* kvm; } ;
struct TYPE_5__ {scalar_t__ invalid; } ;
struct kvm_mmu_page {TYPE_1__ role; int /*<<< orphan*/  root_count; } ;
typedef  int hpa_t ;
struct TYPE_8__ {int /*<<< orphan*/  mmu_lock; } ;

/* Variables and functions */
 void* INVALID_PAGE ; 
 int PT64_BASE_ADDR_MASK ; 
 scalar_t__ PT64_ROOT_LEVEL ; 
 int /*<<< orphan*/  VALID_PAGE (int) ; 
 int /*<<< orphan*/  kvm_mmu_zap_page (TYPE_4__*,struct kvm_mmu_page*) ; 
 struct kvm_mmu_page* page_header (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mmu_free_roots(struct kvm_vcpu *vcpu)
{
	int i;
	struct kvm_mmu_page *sp;

	if (!VALID_PAGE(vcpu->arch.mmu.root_hpa))
		return;
	spin_lock(&vcpu->kvm->mmu_lock);
	if (vcpu->arch.mmu.shadow_root_level == PT64_ROOT_LEVEL) {
		hpa_t root = vcpu->arch.mmu.root_hpa;

		sp = page_header(root);
		--sp->root_count;
		if (!sp->root_count && sp->role.invalid)
			kvm_mmu_zap_page(vcpu->kvm, sp);
		vcpu->arch.mmu.root_hpa = INVALID_PAGE;
		spin_unlock(&vcpu->kvm->mmu_lock);
		return;
	}
	for (i = 0; i < 4; ++i) {
		hpa_t root = vcpu->arch.mmu.pae_root[i];

		if (root) {
			root &= PT64_BASE_ADDR_MASK;
			sp = page_header(root);
			--sp->root_count;
			if (!sp->root_count && sp->role.invalid)
				kvm_mmu_zap_page(vcpu->kvm, sp);
		}
		vcpu->arch.mmu.pae_root[i] = INVALID_PAGE;
	}
	spin_unlock(&vcpu->kvm->mmu_lock);
	vcpu->arch.mmu.root_hpa = INVALID_PAGE;
}