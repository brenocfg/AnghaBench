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
struct TYPE_2__ {scalar_t__ level; } ;
struct kvm_mmu_page {scalar_t__ unsync; TYPE_1__ role; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 scalar_t__ PT_PAGE_TABLE_LEVEL ; 
 struct kvm_mmu_page* kvm_mmu_lookup_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kvm_unsync_page (struct kvm_vcpu*,struct kvm_mmu_page*) ; 
 scalar_t__ oos_shadow ; 

__attribute__((used)) static int mmu_need_write_protect(struct kvm_vcpu *vcpu, gfn_t gfn,
				  bool can_unsync)
{
	struct kvm_mmu_page *shadow;

	shadow = kvm_mmu_lookup_page(vcpu->kvm, gfn);
	if (shadow) {
		if (shadow->role.level != PT_PAGE_TABLE_LEVEL)
			return 1;
		if (shadow->unsync)
			return 0;
		if (can_unsync && oos_shadow)
			return kvm_unsync_page(vcpu, shadow);
		return 1;
	}
	return 0;
}