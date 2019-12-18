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
struct TYPE_2__ {int /*<<< orphan*/  guest_fpu; } ;
struct kvm_vcpu {int guest_fpu_loaded; TYPE_1__ arch; int /*<<< orphan*/  fpu_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  fpu_restore_checking (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernel_fpu_begin () ; 
 int /*<<< orphan*/  kvm_put_guest_xcr0 (struct kvm_vcpu*) ; 

void kvm_load_guest_fpu(struct kvm_vcpu *vcpu)
{
	if (!vcpu->fpu_active || vcpu->guest_fpu_loaded)
		return;

	/*
	 * Restore all possible states in the guest,
	 * and assume host would use all available bits.
	 * Guest xcr0 would be loaded later.
	 */
	kvm_put_guest_xcr0(vcpu);
	vcpu->guest_fpu_loaded = 1;
	kernel_fpu_begin();
	fpu_restore_checking(&vcpu->arch.guest_fpu);
}