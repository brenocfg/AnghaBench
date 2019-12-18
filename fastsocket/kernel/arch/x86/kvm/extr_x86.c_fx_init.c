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
struct TYPE_2__ {int /*<<< orphan*/  cr0; int /*<<< orphan*/  xcr0; int /*<<< orphan*/  guest_fpu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_CR0_ET ; 
 int /*<<< orphan*/  XSTATE_FP ; 
 int /*<<< orphan*/  fpu_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fpu_finit (int /*<<< orphan*/ *) ; 

void fx_init(struct kvm_vcpu *vcpu)
{
	fpu_alloc(&vcpu->arch.guest_fpu);
	fpu_finit(&vcpu->arch.guest_fpu);

	/*
	 * Ensure guest xcr0 is valid for loading
	 */
	vcpu->arch.xcr0 = XSTATE_FP;

	vcpu->arch.cr0 |= X86_CR0_ET;
}