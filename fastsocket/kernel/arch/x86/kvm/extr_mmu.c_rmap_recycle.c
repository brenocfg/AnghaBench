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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct TYPE_2__ {int /*<<< orphan*/  level; } ;
struct kvm_mmu_page {TYPE_1__ role; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ *) ; 
 unsigned long* gfn_to_rmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_flush_remote_tlbs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_unmap_rmapp (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ; 
 struct kvm_mmu_page* page_header (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unalias_gfn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rmap_recycle(struct kvm_vcpu *vcpu, u64 *spte, gfn_t gfn)
{
	unsigned long *rmapp;
	struct kvm_mmu_page *sp;

	sp = page_header(__pa(spte));

	gfn = unalias_gfn(vcpu->kvm, gfn);
	rmapp = gfn_to_rmap(vcpu->kvm, gfn, sp->role.level);

	kvm_unmap_rmapp(vcpu->kvm, rmapp, 0);
	kvm_flush_remote_tlbs(vcpu->kvm);
}