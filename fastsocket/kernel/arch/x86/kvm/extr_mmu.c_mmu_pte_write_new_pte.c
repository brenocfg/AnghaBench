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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {TYPE_2__* kvm; } ;
struct TYPE_6__ {scalar_t__ level; scalar_t__ glevels; } ;
struct kvm_mmu_page {TYPE_3__ role; } ;
struct TYPE_4__ {int /*<<< orphan*/  mmu_pte_updated; int /*<<< orphan*/  mmu_pde_zapped; } ;
struct TYPE_5__ {TYPE_1__ stat; } ;

/* Variables and functions */
 scalar_t__ PT32_ROOT_LEVEL ; 
 scalar_t__ PT_PAGE_TABLE_LEVEL ; 
 int /*<<< orphan*/  paging32_update_pte (struct kvm_vcpu*,struct kvm_mmu_page*,int /*<<< orphan*/ *,void const*) ; 
 int /*<<< orphan*/  paging64_update_pte (struct kvm_vcpu*,struct kvm_mmu_page*,int /*<<< orphan*/ *,void const*) ; 

__attribute__((used)) static void mmu_pte_write_new_pte(struct kvm_vcpu *vcpu,
				  struct kvm_mmu_page *sp,
				  u64 *spte,
				  const void *new)
{
	if (sp->role.level != PT_PAGE_TABLE_LEVEL) {
		++vcpu->kvm->stat.mmu_pde_zapped;
		return;
        }

	++vcpu->kvm->stat.mmu_pte_updated;
	if (sp->role.glevels == PT32_ROOT_LEVEL)
		paging32_update_pte(vcpu, sp, spte, new);
	else
		paging64_update_pte(vcpu, sp, spte, new);
}