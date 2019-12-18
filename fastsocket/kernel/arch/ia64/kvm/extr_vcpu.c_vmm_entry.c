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
struct TYPE_2__ {scalar_t__ vpd; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAL_VPS_RESTORE ; 
 struct kvm_vcpu* current_vcpu ; 
 int /*<<< orphan*/  ia64_call_vsa (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_vcpu (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_init_all_rr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_init_vhpt (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_init_vtlb (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmm_reset_entry () ; 

int vmm_entry(void)
{
	struct kvm_vcpu *v;
	v = current_vcpu;

	ia64_call_vsa(PAL_VPS_RESTORE, (unsigned long)v->arch.vpd,
						0, 0, 0, 0, 0, 0);
	kvm_init_vtlb(v);
	kvm_init_vhpt(v);
	init_vcpu(v);
	kvm_init_all_rr(v);
	vmm_reset_entry();

	return 0;
}