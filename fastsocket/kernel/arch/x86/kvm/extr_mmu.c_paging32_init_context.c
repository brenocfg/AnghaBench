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
struct kvm_mmu {int /*<<< orphan*/  root_hpa; int /*<<< orphan*/  shadow_root_level; int /*<<< orphan*/  root_level; int /*<<< orphan*/  invlpg; int /*<<< orphan*/  sync_page; int /*<<< orphan*/  prefetch_page; int /*<<< orphan*/  free; int /*<<< orphan*/  gva_to_gpa; int /*<<< orphan*/  page_fault; int /*<<< orphan*/  new_cr3; } ;
struct TYPE_2__ {struct kvm_mmu mmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_PAGE ; 
 int /*<<< orphan*/  PT32E_ROOT_LEVEL ; 
 int /*<<< orphan*/  PT32_ROOT_LEVEL ; 
 int /*<<< orphan*/  paging32_gva_to_gpa ; 
 int /*<<< orphan*/  paging32_invlpg ; 
 int /*<<< orphan*/  paging32_page_fault ; 
 int /*<<< orphan*/  paging32_prefetch_page ; 
 int /*<<< orphan*/  paging32_sync_page ; 
 int /*<<< orphan*/  paging_free ; 
 int /*<<< orphan*/  paging_new_cr3 ; 
 int /*<<< orphan*/  reset_rsvds_bits_mask (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int paging32_init_context(struct kvm_vcpu *vcpu)
{
	struct kvm_mmu *context = &vcpu->arch.mmu;

	reset_rsvds_bits_mask(vcpu, PT32_ROOT_LEVEL);
	context->new_cr3 = paging_new_cr3;
	context->page_fault = paging32_page_fault;
	context->gva_to_gpa = paging32_gva_to_gpa;
	context->free = paging_free;
	context->prefetch_page = paging32_prefetch_page;
	context->sync_page = paging32_sync_page;
	context->invlpg = paging32_invlpg;
	context->root_level = PT32_ROOT_LEVEL;
	context->shadow_root_level = PT32E_ROOT_LEVEL;
	context->root_hpa = INVALID_PAGE;
	return 0;
}