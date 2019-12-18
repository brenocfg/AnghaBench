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
struct TYPE_5__ {int invalid; int /*<<< orphan*/  direct; } ;
struct kvm_mmu_page {int /*<<< orphan*/  link; TYPE_2__ role; int /*<<< orphan*/  hash_link; int /*<<< orphan*/  root_count; scalar_t__ unsync; int /*<<< orphan*/  gfn; } ;
struct TYPE_6__ {int /*<<< orphan*/  active_mmu_pages; } ;
struct TYPE_4__ {int /*<<< orphan*/  mmu_shadow_zapped; } ;
struct kvm {TYPE_3__ arch; TYPE_1__ stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_flush_remote_tlbs (struct kvm*) ; 
 int /*<<< orphan*/  kvm_mmu_free_page (struct kvm*,struct kvm_mmu_page*) ; 
 int /*<<< orphan*/  kvm_mmu_page_unlink_children (struct kvm*,struct kvm_mmu_page*) ; 
 int /*<<< orphan*/  kvm_mmu_reset_last_pte_updated (struct kvm*) ; 
 int /*<<< orphan*/  kvm_mmu_unlink_parents (struct kvm*,struct kvm_mmu_page*) ; 
 int /*<<< orphan*/  kvm_reload_remote_mmus (struct kvm*) ; 
 int /*<<< orphan*/  kvm_unlink_unsync_page (struct kvm*,struct kvm_mmu_page*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mmu_zap_unsync_children (struct kvm*,struct kvm_mmu_page*) ; 
 int /*<<< orphan*/  trace_kvm_mmu_zap_page (struct kvm_mmu_page*) ; 
 int /*<<< orphan*/  unaccount_shadowed (struct kvm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_mmu_zap_page(struct kvm *kvm, struct kvm_mmu_page *sp)
{
	int ret;

	trace_kvm_mmu_zap_page(sp);
	++kvm->stat.mmu_shadow_zapped;
	ret = mmu_zap_unsync_children(kvm, sp);
	kvm_mmu_page_unlink_children(kvm, sp);
	kvm_mmu_unlink_parents(kvm, sp);
	kvm_flush_remote_tlbs(kvm);
	if (!sp->role.invalid && !sp->role.direct)
		unaccount_shadowed(kvm, sp->gfn);
	if (sp->unsync)
		kvm_unlink_unsync_page(kvm, sp);
	if (!sp->root_count) {
		hlist_del(&sp->hash_link);
		kvm_mmu_free_page(kvm, sp);
	} else {
		sp->role.invalid = 1;
		list_move(&sp->link, &kvm->arch.active_mmu_pages);
		kvm_reload_remote_mmus(kvm);
	}
	kvm_mmu_reset_last_pte_updated(kvm);
	return ret;
}