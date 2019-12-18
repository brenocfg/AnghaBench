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
typedef  scalar_t__ u64 ;
struct thash_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * dtrs; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ PAGEALIGN (scalar_t__,scalar_t__) ; 
 scalar_t__ PAGE_FLAGS_RV_MASK ; 
 scalar_t__ PAGE_SHIFT ; 
 scalar_t__ RR_RID_MASK ; 
 int /*<<< orphan*/  VMX (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ VTLB_PTE_IO ; 
 scalar_t__ _PAGE_PPN_MASK ; 
 scalar_t__ _PAGE_SIZE_16M ; 
 scalar_t__ __gpfn_is_io (scalar_t__) ; 
 int /*<<< orphan*/  dtr_regions ; 
 scalar_t__ itir_ps (scalar_t__) ; 
 int /*<<< orphan*/  thash_purge_entries (struct kvm_vcpu*,scalar_t__,scalar_t__) ; 
 scalar_t__ vcpu_get_rr (struct kvm_vcpu*,scalar_t__) ; 
 int /*<<< orphan*/  vcpu_quick_region_set (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vcpu_set_tr (struct thash_data*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

void vcpu_itr_d(struct kvm_vcpu *vcpu, u64 slot, u64 pte, u64 itir, u64 ifa)
{
	u64 gpfn;
	u64 ps, va, rid;
	struct thash_data *p_dtr;

	ps = itir_ps(itir);
	va = PAGEALIGN(ifa, ps);
	pte &= ~PAGE_FLAGS_RV_MASK;

	if (ps != _PAGE_SIZE_16M)
		thash_purge_entries(vcpu, va, ps);
	gpfn = (pte & _PAGE_PPN_MASK) >> PAGE_SHIFT;
	if (__gpfn_is_io(gpfn))
		pte |= VTLB_PTE_IO;
	rid = vcpu_get_rr(vcpu, va);
	rid = rid & RR_RID_MASK;
	p_dtr = (struct thash_data *)&vcpu->arch.dtrs[slot];
	vcpu_set_tr((struct thash_data *)&vcpu->arch.dtrs[slot],
							pte, itir, va, rid);
	vcpu_quick_region_set(VMX(vcpu, dtr_regions), va);
}