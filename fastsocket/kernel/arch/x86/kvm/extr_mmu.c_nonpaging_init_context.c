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
struct kvm_mmu {int /*<<< orphan*/  root_hpa; int /*<<< orphan*/  shadow_root_level; scalar_t__ root_level; int /*<<< orphan*/  invlpg; int /*<<< orphan*/  sync_page; int /*<<< orphan*/  prefetch_page; int /*<<< orphan*/  free; int /*<<< orphan*/  gva_to_gpa; int /*<<< orphan*/  page_fault; int /*<<< orphan*/  new_cr3; } ;
struct TYPE_2__ {struct kvm_mmu mmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_PAGE ; 
 int /*<<< orphan*/  PT32E_ROOT_LEVEL ; 
 int /*<<< orphan*/  nonpaging_free ; 
 int /*<<< orphan*/  nonpaging_gva_to_gpa ; 
 int /*<<< orphan*/  nonpaging_invlpg ; 
 int /*<<< orphan*/  nonpaging_new_cr3 ; 
 int /*<<< orphan*/  nonpaging_page_fault ; 
 int /*<<< orphan*/  nonpaging_prefetch_page ; 
 int /*<<< orphan*/  nonpaging_sync_page ; 

__attribute__((used)) static int nonpaging_init_context(struct kvm_vcpu *vcpu)
{
	struct kvm_mmu *context = &vcpu->arch.mmu;

	context->new_cr3 = nonpaging_new_cr3;
	context->page_fault = nonpaging_page_fault;
	context->gva_to_gpa = nonpaging_gva_to_gpa;
	context->free = nonpaging_free;
	context->prefetch_page = nonpaging_prefetch_page;
	context->sync_page = nonpaging_sync_page;
	context->invlpg = nonpaging_invlpg;
	context->root_level = 0;
	context->shadow_root_level = PT32E_ROOT_LEVEL;
	context->root_hpa = INVALID_PAGE;
	return 0;
}