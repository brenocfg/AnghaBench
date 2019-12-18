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
struct TYPE_2__ {scalar_t__ vpd; int /*<<< orphan*/  host; int /*<<< orphan*/  guest; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAL_VPS_RESTORE ; 
 int /*<<< orphan*/  PAL_VPS_SAVE ; 
 int /*<<< orphan*/  ia64_call_vsa (int /*<<< orphan*/ ,unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_do_resume_op (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmm_trampoline (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void vmm_transition(struct kvm_vcpu *vcpu)
{
	ia64_call_vsa(PAL_VPS_SAVE, (unsigned long)vcpu->arch.vpd,
			1, 0, 0, 0, 0, 0);
	vmm_trampoline(&vcpu->arch.guest, &vcpu->arch.host);
	ia64_call_vsa(PAL_VPS_RESTORE, (unsigned long)vcpu->arch.vpd,
						1, 0, 0, 0, 0, 0);
	kvm_do_resume_op(vcpu);
}