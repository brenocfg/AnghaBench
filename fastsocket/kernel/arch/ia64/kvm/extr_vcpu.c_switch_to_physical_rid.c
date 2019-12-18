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
struct TYPE_2__ {int /*<<< orphan*/  metaphysical_rr4; int /*<<< orphan*/  metaphysical_rr0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int VRN0 ; 
 int VRN4 ; 
 int VRN_SHIFT ; 
 unsigned long ia64_clear_ic () ; 
 int /*<<< orphan*/  ia64_set_psr (unsigned long) ; 
 int /*<<< orphan*/  ia64_set_rr (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia64_srlz_d () ; 

void switch_to_physical_rid(struct kvm_vcpu *vcpu)
{
	unsigned long psr;

	/* Save original virtual mode rr[0] and rr[4] */
	psr = ia64_clear_ic();
	ia64_set_rr(VRN0<<VRN_SHIFT, vcpu->arch.metaphysical_rr0);
	ia64_srlz_d();
	ia64_set_rr(VRN4<<VRN_SHIFT, vcpu->arch.metaphysical_rr4);
	ia64_srlz_d();

	ia64_set_psr(psr);
	return;
}