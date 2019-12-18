#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  root_hpa; } ;
struct TYPE_6__ {TYPE_1__ mmu; } ;
struct kvm_vcpu {TYPE_3__* kvm; TYPE_2__ arch; } ;
typedef  int /*<<< orphan*/  pfn_t ;
typedef  int gva_t ;
typedef  int gfn_t ;
struct TYPE_7__ {unsigned long mmu_notifier_seq; int /*<<< orphan*/  mmu_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct kvm_vcpu*) ; 
 int KVM_PAGES_PER_HPAGE (int) ; 
 int PAGE_SHIFT ; 
 int PFERR_WRITE_MASK ; 
 struct kvm_vcpu* VALID_PAGE (int /*<<< orphan*/ ) ; 
 int __direct_map (struct kvm_vcpu*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfn_to_pfn (TYPE_3__*,int) ; 
 scalar_t__ is_error_pfn (int /*<<< orphan*/ ) ; 
 int kvm_handle_bad_page (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_mmu_free_some_pages (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_release_pfn_clean (int /*<<< orphan*/ ) ; 
 int mapping_level (struct kvm_vcpu*,int) ; 
 scalar_t__ mmu_notifier_retry (struct kvm_vcpu*,unsigned long) ; 
 int mmu_topup_memory_caches (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tdp_page_fault(struct kvm_vcpu *vcpu, gva_t gpa,
				u32 error_code)
{
	pfn_t pfn;
	int r;
	int level;
	gfn_t gfn = gpa >> PAGE_SHIFT;
	unsigned long mmu_seq;

	ASSERT(vcpu);
	ASSERT(VALID_PAGE(vcpu->arch.mmu.root_hpa));

	r = mmu_topup_memory_caches(vcpu);
	if (r)
		return r;

	mmu_seq = vcpu->kvm->mmu_notifier_seq;
	smp_rmb();
	level = mapping_level(vcpu, gfn);

	gfn &= ~(KVM_PAGES_PER_HPAGE(level) - 1);

	pfn = gfn_to_pfn(vcpu->kvm, gfn);
	if (is_error_pfn(pfn))
		return kvm_handle_bad_page(vcpu->kvm, gfn, pfn);
	spin_lock(&vcpu->kvm->mmu_lock);
	if (mmu_notifier_retry(vcpu, mmu_seq))
		goto out_unlock;
	kvm_mmu_free_some_pages(vcpu);
	r = __direct_map(vcpu, gpa, error_code & PFERR_WRITE_MASK,
			 level, gfn, pfn);
	spin_unlock(&vcpu->kvm->mmu_lock);

	return r;

out_unlock:
	spin_unlock(&vcpu->kvm->mmu_lock);
	kvm_release_pfn_clean(pfn);
	return 0;
}