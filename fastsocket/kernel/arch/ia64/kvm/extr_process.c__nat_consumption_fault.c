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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {int dummy; } ;
typedef  enum tlb_miss_type { ____Placeholder_tlb_miss_type } tlb_miss_type ;

/* Variables and functions */
 int DATA ; 
 int /*<<< orphan*/  IA64_NAT_CONSUMPTION_VECTOR ; 
 int INSTRUCTION ; 
 int /*<<< orphan*/  inject_guest_interruption (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ifa_itir_iha (struct kvm_vcpu*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _nat_consumption_fault(struct kvm_vcpu *vcpu, u64 vadr,
						enum tlb_miss_type t)
{
	/* If vPSR.ic && t == DATA/INST, IFA */
	if (t == DATA || t == INSTRUCTION) {
		/* IFA */
		set_ifa_itir_iha(vcpu, vadr, 1, 0, 0);
	}

	inject_guest_interruption(vcpu, IA64_NAT_CONSUMPTION_VECTOR);
}