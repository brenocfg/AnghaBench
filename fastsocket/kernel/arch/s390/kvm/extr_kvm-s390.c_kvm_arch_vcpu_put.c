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
struct TYPE_2__ {int /*<<< orphan*/  host_acrs; int /*<<< orphan*/  host_fpregs; int /*<<< orphan*/  guest_acrs; int /*<<< orphan*/  guest_fpregs; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  restore_access_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_fp_regs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save_access_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_fp_regs (int /*<<< orphan*/ *) ; 

void kvm_arch_vcpu_put(struct kvm_vcpu *vcpu)
{
	save_fp_regs(&vcpu->arch.guest_fpregs);
	save_access_regs(vcpu->arch.guest_acrs);
	restore_fp_regs(&vcpu->arch.host_fpregs);
	restore_access_regs(vcpu->arch.host_acrs);
}