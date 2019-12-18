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
struct TYPE_4__ {int /*<<< orphan*/  fpc; } ;
struct TYPE_3__ {int /*<<< orphan*/  guest_acrs; TYPE_2__ guest_fpregs; int /*<<< orphan*/  host_acrs; int /*<<< orphan*/  host_fpregs; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPC_VALID_MASK ; 
 int /*<<< orphan*/  restore_access_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_fp_regs (TYPE_2__*) ; 
 int /*<<< orphan*/  save_access_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_fp_regs (int /*<<< orphan*/ *) ; 

void kvm_arch_vcpu_load(struct kvm_vcpu *vcpu, int cpu)
{
	save_fp_regs(&vcpu->arch.host_fpregs);
	save_access_regs(vcpu->arch.host_acrs);
	vcpu->arch.guest_fpregs.fpc &= FPC_VALID_MASK;
	restore_fp_regs(&vcpu->arch.guest_fpregs);
	restore_access_regs(vcpu->arch.guest_acrs);
}