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
typedef  size_t u64 ;
struct thash_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * itrs; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 size_t PAGEALIGN (size_t,size_t) ; 
 size_t PAGE_FLAGS_RV_MASK ; 
 size_t RR_RID_MASK ; 
 int /*<<< orphan*/  VMX (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 size_t itir_ps (size_t) ; 
 int /*<<< orphan*/  itr_regions ; 
 size_t vcpu_get_rr (struct kvm_vcpu*,size_t) ; 
 int /*<<< orphan*/  vcpu_quick_region_set (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  vcpu_set_tr (struct thash_data*,size_t,size_t,size_t,size_t) ; 

void vcpu_itr_i(struct kvm_vcpu *vcpu, u64 slot, u64 pte, u64 itir, u64 ifa)
{
	u64 ps, va, rid;
	struct thash_data *p_itr;

	ps = itir_ps(itir);
	va = PAGEALIGN(ifa, ps);
	pte &= ~PAGE_FLAGS_RV_MASK;
	rid = vcpu_get_rr(vcpu, ifa);
	rid = rid & RR_RID_MASK;
	p_itr = (struct thash_data *)&vcpu->arch.itrs[slot];
	vcpu_set_tr(p_itr, pte, itir, va, rid);
	vcpu_quick_region_set(VMX(vcpu, itr_regions), va);
}