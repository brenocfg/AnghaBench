#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kvm_mmu {void* root_level; void* gva_to_gpa; int /*<<< orphan*/  root_hpa; int /*<<< orphan*/  shadow_root_level; int /*<<< orphan*/  invlpg; int /*<<< orphan*/  sync_page; int /*<<< orphan*/  prefetch_page; int /*<<< orphan*/  free; int /*<<< orphan*/  page_fault; int /*<<< orphan*/  new_cr3; } ;
struct TYPE_3__ {struct kvm_mmu mmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_tdp_level ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_PAGE ; 
 void* PT32E_ROOT_LEVEL ; 
 void* PT32_ROOT_LEVEL ; 
 void* PT64_ROOT_LEVEL ; 
 scalar_t__ is_long_mode (struct kvm_vcpu*) ; 
 scalar_t__ is_pae (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_paging (struct kvm_vcpu*) ; 
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  nonpaging_free ; 
 void* nonpaging_gva_to_gpa ; 
 int /*<<< orphan*/  nonpaging_invlpg ; 
 int /*<<< orphan*/  nonpaging_new_cr3 ; 
 int /*<<< orphan*/  nonpaging_prefetch_page ; 
 int /*<<< orphan*/  nonpaging_sync_page ; 
 void* paging32_gva_to_gpa ; 
 void* paging64_gva_to_gpa ; 
 int /*<<< orphan*/  reset_rsvds_bits_mask (struct kvm_vcpu*,void*) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  tdp_page_fault ; 

__attribute__((used)) static int init_kvm_tdp_mmu(struct kvm_vcpu *vcpu)
{
	struct kvm_mmu *context = &vcpu->arch.mmu;

	context->new_cr3 = nonpaging_new_cr3;
	context->page_fault = tdp_page_fault;
	context->free = nonpaging_free;
	context->prefetch_page = nonpaging_prefetch_page;
	context->sync_page = nonpaging_sync_page;
	context->invlpg = nonpaging_invlpg;
	context->shadow_root_level = kvm_x86_ops->get_tdp_level();
	context->root_hpa = INVALID_PAGE;

	if (!is_paging(vcpu)) {
		context->gva_to_gpa = nonpaging_gva_to_gpa;
		context->root_level = 0;
	} else if (is_long_mode(vcpu)) {
		reset_rsvds_bits_mask(vcpu, PT64_ROOT_LEVEL);
		context->gva_to_gpa = paging64_gva_to_gpa;
		context->root_level = PT64_ROOT_LEVEL;
	} else if (is_pae(vcpu)) {
		reset_rsvds_bits_mask(vcpu, PT32E_ROOT_LEVEL);
		context->gva_to_gpa = paging64_gva_to_gpa;
		context->root_level = PT32E_ROOT_LEVEL;
	} else {
		reset_rsvds_bits_mask(vcpu, PT32_ROOT_LEVEL);
		context->gva_to_gpa = paging32_gva_to_gpa;
		context->root_level = PT32_ROOT_LEVEL;
	}

	return 0;
}