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
struct kvm_mmu_page {int /*<<< orphan*/  gfns; int /*<<< orphan*/  spt; int /*<<< orphan*/  link; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_empty_shadow_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct kvm_mmu_page*) ; 
 int /*<<< orphan*/  kvm_mod_used_mmu_pages (struct kvm*,int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_mmu_free_page(struct kvm *kvm, struct kvm_mmu_page *sp)
{
	ASSERT(is_empty_shadow_page(sp->spt));
	list_del(&sp->link);
	__free_page(virt_to_page(sp->spt));
	__free_page(virt_to_page(sp->gfns));
	kfree(sp);
	kvm_mod_used_mmu_pages(kvm, -1);
}