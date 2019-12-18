#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  unsigned int u32 ;
struct TYPE_6__ {unsigned int* regs; } ;
struct TYPE_7__ {TYPE_1__ arch; } ;
struct vcpu_svm {TYPE_2__ vcpu; scalar_t__ next_rip; } ;
struct msr_data {int data; unsigned int index; int host_initiated; } ;

/* Variables and functions */
 size_t VCPU_REGS_RAX ; 
 size_t VCPU_REGS_RCX ; 
 size_t VCPU_REGS_RDX ; 
 int /*<<< orphan*/  kvm_inject_gp (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_rip_read (TYPE_2__*) ; 
 int /*<<< orphan*/  skip_emulated_instruction (TYPE_2__*) ; 
 scalar_t__ svm_set_msr (TYPE_2__*,struct msr_data*) ; 
 int /*<<< orphan*/  trace_kvm_msr_write (unsigned int,int) ; 

__attribute__((used)) static int wrmsr_interception(struct vcpu_svm *svm)
{
	struct msr_data msr;
	u32 ecx = svm->vcpu.arch.regs[VCPU_REGS_RCX];
	u64 data = (svm->vcpu.arch.regs[VCPU_REGS_RAX] & -1u)
		| ((u64)(svm->vcpu.arch.regs[VCPU_REGS_RDX] & -1u) << 32);

	trace_kvm_msr_write(ecx, data);

	msr.data = data;
	msr.index = ecx;
	msr.host_initiated = false;

	svm->next_rip = kvm_rip_read(&svm->vcpu) + 2;
	if (svm_set_msr(&svm->vcpu, &msr))
		kvm_inject_gp(&svm->vcpu, 0);
	else
		skip_emulated_instruction(&svm->vcpu);
	return 1;
}