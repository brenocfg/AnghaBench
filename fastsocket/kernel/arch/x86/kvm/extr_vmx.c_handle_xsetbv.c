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
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_REGS_RCX ; 
 int /*<<< orphan*/  kvm_read_edx_eax (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_register_read (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_set_xcr (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_emulated_instruction (struct kvm_vcpu*) ; 

__attribute__((used)) static int handle_xsetbv(struct kvm_vcpu *vcpu)
{
	u64 new_bv = kvm_read_edx_eax(vcpu);
	u32 index = kvm_register_read(vcpu, VCPU_REGS_RCX);

	if (kvm_set_xcr(vcpu, index, new_bv) == 0)
		skip_emulated_instruction(vcpu);
	return 1;
}