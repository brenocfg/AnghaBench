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
struct TYPE_4__ {int /*<<< orphan*/  mmu_page_cache; int /*<<< orphan*/  mmu_page_header_cache; } ;
struct kvm_vcpu {TYPE_3__* kvm; TYPE_1__ arch; } ;
struct kvm_mmu_page {int /*<<< orphan*/ * parent_pte; scalar_t__ multimapped; int /*<<< orphan*/  slot_bitmap; int /*<<< orphan*/  oos_link; int /*<<< orphan*/  link; void* spt; void* gfns; } ;
struct TYPE_5__ {int /*<<< orphan*/  active_mmu_pages; } ;
struct TYPE_6__ {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ KVM_MEMORY_SLOTS ; 
 scalar_t__ KVM_PRIVATE_MEM_SLOTS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kvm_mod_used_mmu_pages (TYPE_3__*,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* mmu_memory_cache_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_page_private (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  virt_to_page (void*) ; 

__attribute__((used)) static struct kvm_mmu_page *kvm_mmu_alloc_page(struct kvm_vcpu *vcpu,
					       u64 *parent_pte)
{
	struct kvm_mmu_page *sp;

	sp = mmu_memory_cache_alloc(&vcpu->arch.mmu_page_header_cache, sizeof *sp);
	sp->spt = mmu_memory_cache_alloc(&vcpu->arch.mmu_page_cache, PAGE_SIZE);
	sp->gfns = mmu_memory_cache_alloc(&vcpu->arch.mmu_page_cache, PAGE_SIZE);
	set_page_private(virt_to_page(sp->spt), (unsigned long)sp);
	list_add(&sp->link, &vcpu->kvm->arch.active_mmu_pages);
	INIT_LIST_HEAD(&sp->oos_link);
	bitmap_zero(sp->slot_bitmap, KVM_MEMORY_SLOTS + KVM_PRIVATE_MEM_SLOTS);
	sp->multimapped = 0;
	sp->parent_pte = parent_pte;
	kvm_mod_used_mmu_pages(vcpu->kvm, +1);
	return sp;
}