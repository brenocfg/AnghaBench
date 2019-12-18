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
struct kvm_mmu {int root_level; int shadow_root_level; int /*<<< orphan*/  root_hpa; int /*<<< orphan*/  free; int /*<<< orphan*/  invlpg; int /*<<< orphan*/  sync_page; int /*<<< orphan*/  prefetch_page; int /*<<< orphan*/  gva_to_gpa; int /*<<< orphan*/  page_fault; int /*<<< orphan*/  new_cr3; } ;
struct TYPE_2__ {struct kvm_mmu mmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INVALID_PAGE ; 
 int /*<<< orphan*/  is_pae (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  paging64_gva_to_gpa ; 
 int /*<<< orphan*/  paging64_invlpg ; 
 int /*<<< orphan*/  paging64_page_fault ; 
 int /*<<< orphan*/  paging64_prefetch_page ; 
 int /*<<< orphan*/  paging64_sync_page ; 
 int /*<<< orphan*/  paging_free ; 
 int /*<<< orphan*/  paging_new_cr3 ; 

__attribute__((used)) static int paging64_init_context_common(struct kvm_vcpu *vcpu, int level)
{
	struct kvm_mmu *context = &vcpu->arch.mmu;

	ASSERT(is_pae(vcpu));
	context->new_cr3 = paging_new_cr3;
	context->page_fault = paging64_page_fault;
	context->gva_to_gpa = paging64_gva_to_gpa;
	context->prefetch_page = paging64_prefetch_page;
	context->sync_page = paging64_sync_page;
	context->invlpg = paging64_invlpg;
	context->free = paging_free;
	context->root_level = level;
	context->shadow_root_level = level;
	context->root_hpa = INVALID_PAGE;
	return 0;
}