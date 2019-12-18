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
typedef  int u64 ;
struct thash_data {int ppn; int ps; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_3__ {int* i64; } ;
typedef  TYPE_1__ IA64_BUNDLE ;

/* Variables and functions */
 int ARCH_PAGE_SHIFT ; 
 int IA64_FAULT ; 
 int IA64_NO_FAULT ; 
 int IA64_PSR_IT ; 
 int /*<<< orphan*/  I_TLB ; 
 int PSIZE (int) ; 
 int VCPU (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ __kvm_va (int) ; 
 int /*<<< orphan*/  ia64_ptcl (int,int) ; 
 int kvm_gpa_to_mpa (int) ; 
 struct thash_data* vhpt_lookup (int) ; 
 int /*<<< orphan*/  vpsr ; 
 struct thash_data* vtlb_lookup (struct kvm_vcpu*,int,int /*<<< orphan*/ ) ; 

int fetch_code(struct kvm_vcpu *vcpu, u64 gip, IA64_BUNDLE *pbundle)
{
	u64     gpip = 0;   /* guest physical IP*/
	u64     *vpa;
	struct thash_data    *tlb;
	u64     maddr;

	if (!(VCPU(vcpu, vpsr) & IA64_PSR_IT)) {
		/* I-side physical mode */
		gpip = gip;
	} else {
		tlb = vtlb_lookup(vcpu, gip, I_TLB);
		if (tlb)
			gpip = (tlb->ppn >> (tlb->ps - 12) << tlb->ps) |
				(gip & (PSIZE(tlb->ps) - 1));
	}
	if (gpip) {
		maddr = kvm_gpa_to_mpa(gpip);
	} else {
		tlb = vhpt_lookup(gip);
		if (tlb == NULL) {
			ia64_ptcl(gip, ARCH_PAGE_SHIFT << 2);
			return IA64_FAULT;
		}
		maddr = (tlb->ppn >> (tlb->ps - 12) << tlb->ps)
					| (gip & (PSIZE(tlb->ps) - 1));
	}
	vpa = (u64 *)__kvm_va(maddr);

	pbundle->i64[0] = *vpa++;
	pbundle->i64[1] = *vpa;

	return IA64_NO_FAULT;
}