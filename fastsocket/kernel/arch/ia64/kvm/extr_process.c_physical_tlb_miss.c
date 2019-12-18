#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
union ia64_rr {int ps; int /*<<< orphan*/  val; } ;
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 unsigned long PHY_PAGE_WB ; 
 unsigned long _PAGE_PPN_MASK ; 
 int /*<<< orphan*/  ia64_get_rr (unsigned long) ; 
 int /*<<< orphan*/  thash_vhpt_insert (struct kvm_vcpu*,unsigned long,int /*<<< orphan*/ ,unsigned long,int) ; 

void physical_tlb_miss(struct kvm_vcpu *vcpu, unsigned long vadr, int type)
{
	unsigned long pte;
	union ia64_rr rr;

	rr.val = ia64_get_rr(vadr);
	pte =  vadr & _PAGE_PPN_MASK;
	pte = pte | PHY_PAGE_WB;
	thash_vhpt_insert(vcpu, pte, (u64)(rr.ps << 2), vadr, type);
	return;
}