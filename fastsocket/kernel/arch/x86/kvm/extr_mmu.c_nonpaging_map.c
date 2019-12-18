#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kvm_vcpu {TYPE_1__* kvm; } ;
typedef  int /*<<< orphan*/  pfn_t ;
typedef  int /*<<< orphan*/  gva_t ;
typedef  int gfn_t ;
struct TYPE_3__ {unsigned long mmu_notifier_seq; int /*<<< orphan*/  mmu_lock; } ;

/* Variables and functions */
 int KVM_PAGES_PER_HPAGE (int) ; 
 int PT_DIRECTORY_LEVEL ; 
 int __direct_map (struct kvm_vcpu*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfn_to_pfn (TYPE_1__*,int) ; 
 scalar_t__ is_error_pfn (int /*<<< orphan*/ ) ; 
 int kvm_handle_bad_page (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_mmu_free_some_pages (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_release_pfn_clean (int /*<<< orphan*/ ) ; 
 int mapping_level (struct kvm_vcpu*,int) ; 
 scalar_t__ mmu_notifier_retry (struct kvm_vcpu*,unsigned long) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nonpaging_map(struct kvm_vcpu *vcpu, gva_t v, int write, gfn_t gfn)
{
	int r;
	int level;
	pfn_t pfn;
	unsigned long mmu_seq;

	mmu_seq = vcpu->kvm->mmu_notifier_seq;
	smp_rmb();
	level = mapping_level(vcpu, gfn);

	/*
	 * This path builds a PAE pagetable - so we can map 2mb pages at
	 * maximum. Therefore check if the level is larger than that.
	 */
	if (level > PT_DIRECTORY_LEVEL)
		level = PT_DIRECTORY_LEVEL;

	gfn &= ~(KVM_PAGES_PER_HPAGE(level) - 1);

	pfn = gfn_to_pfn(vcpu->kvm, gfn);

	/* mmio */
	if (is_error_pfn(pfn))
		return kvm_handle_bad_page(vcpu->kvm, gfn, pfn);

	spin_lock(&vcpu->kvm->mmu_lock);
	if (mmu_notifier_retry(vcpu, mmu_seq))
		goto out_unlock;
	kvm_mmu_free_some_pages(vcpu);
	r = __direct_map(vcpu, v, write, level, gfn, pfn);
	spin_unlock(&vcpu->kvm->mmu_lock);


	return r;

out_unlock:
	spin_unlock(&vcpu->kvm->mmu_lock);
	kvm_release_pfn_clean(pfn);
	return 0;
}