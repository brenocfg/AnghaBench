#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fpu_reload; } ;
struct TYPE_3__ {int /*<<< orphan*/  guest_fpu; } ;
struct kvm_vcpu {int /*<<< orphan*/  requests; TYPE_2__ stat; TYPE_1__ arch; scalar_t__ guest_fpu_loaded; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_DEACTIVATE_FPU ; 
 int /*<<< orphan*/  fpu_save_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernel_fpu_end () ; 
 int /*<<< orphan*/  kvm_put_guest_xcr0 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void kvm_put_guest_fpu(struct kvm_vcpu *vcpu)
{
	kvm_put_guest_xcr0(vcpu);

	if (!vcpu->guest_fpu_loaded)
		return;

	vcpu->guest_fpu_loaded = 0;
	fpu_save_init(&vcpu->arch.guest_fpu);
	kernel_fpu_end();
	++vcpu->stat.fpu_reload;
	set_bit(KVM_REQ_DEACTIVATE_FPU, &vcpu->requests);
}