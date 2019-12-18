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
union ia64_rr {int /*<<< orphan*/  val; } ;
union ia64_pta {scalar_t__ vf; int /*<<< orphan*/  val; } ;
typedef  int u64 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAL_VPS_TTAG ; 
 int ia64_call_vsa (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_get_pta (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_get_rr (struct kvm_vcpu*,int) ; 

u64 vcpu_ttag(struct kvm_vcpu *vcpu, u64 vadr)
{
	union ia64_rr vrr;
	union ia64_pta vpta;
	u64 pval;

	vpta.val = vcpu_get_pta(vcpu);
	vrr.val = vcpu_get_rr(vcpu, vadr);
	if (vpta.vf) {
		pval = ia64_call_vsa(PAL_VPS_TTAG, vadr, vrr.val,
						0, 0, 0, 0, 0);
	} else
		pval = 1;

	return  pval;
}