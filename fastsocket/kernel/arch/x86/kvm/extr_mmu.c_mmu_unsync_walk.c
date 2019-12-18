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
struct kvm_mmu_pages {int dummy; } ;
struct kvm_mmu_page {int /*<<< orphan*/  unsync_children; } ;

/* Variables and functions */
 int __mmu_unsync_walk (struct kvm_mmu_page*,struct kvm_mmu_pages*) ; 
 int /*<<< orphan*/  mmu_pages_add (struct kvm_mmu_pages*,struct kvm_mmu_page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmu_unsync_walk(struct kvm_mmu_page *sp,
			   struct kvm_mmu_pages *pvec)
{
	if (!sp->unsync_children)
		return 0;

	mmu_pages_add(pvec, sp, 0);
	return __mmu_unsync_walk(sp, pvec);
}