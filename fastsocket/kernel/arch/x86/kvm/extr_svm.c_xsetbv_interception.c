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
struct vcpu_svm {int /*<<< orphan*/  vcpu; scalar_t__ next_rip; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_REGS_RCX ; 
 int /*<<< orphan*/  kvm_read_edx_eax (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_register_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_rip_read (int /*<<< orphan*/ *) ; 
 scalar_t__ kvm_set_xcr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_emulated_instruction (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xsetbv_interception(struct vcpu_svm *svm)
{
	u64 new_bv = kvm_read_edx_eax(&svm->vcpu);
	u32 index = kvm_register_read(&svm->vcpu, VCPU_REGS_RCX);

	if (kvm_set_xcr(&svm->vcpu, index, new_bv) == 0) {
		svm->next_rip = kvm_rip_read(&svm->vcpu) + 3;
		skip_emulated_instruction(&svm->vcpu);
	}

	return 1;
}