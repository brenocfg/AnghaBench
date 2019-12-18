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
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {int dummy; } ;
struct kvm_cpuid_entry2 {int /*<<< orphan*/  edx; int /*<<< orphan*/  ecx; int /*<<< orphan*/  ebx; int /*<<< orphan*/  eax; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* skip_emulated_instruction ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_REGS_RAX ; 
 int /*<<< orphan*/  VCPU_REGS_RBX ; 
 int /*<<< orphan*/  VCPU_REGS_RCX ; 
 int /*<<< orphan*/  VCPU_REGS_RDX ; 
 struct kvm_cpuid_entry2* check_cpuid_limit (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kvm_cpuid_entry2* kvm_find_cpuid_entry (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_register_read (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_register_write (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_cpuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kvm_emulate_cpuid(struct kvm_vcpu *vcpu)
{
	u32 function, index;
	struct kvm_cpuid_entry2 *best;

	function = kvm_register_read(vcpu, VCPU_REGS_RAX);
	index = kvm_register_read(vcpu, VCPU_REGS_RCX);
	kvm_register_write(vcpu, VCPU_REGS_RAX, 0);
	kvm_register_write(vcpu, VCPU_REGS_RBX, 0);
	kvm_register_write(vcpu, VCPU_REGS_RCX, 0);
	kvm_register_write(vcpu, VCPU_REGS_RDX, 0);
	best = kvm_find_cpuid_entry(vcpu, function, index);

	if (!best)
		best = check_cpuid_limit(vcpu, function, index);

	if (best) {
		kvm_register_write(vcpu, VCPU_REGS_RAX, best->eax);
		kvm_register_write(vcpu, VCPU_REGS_RBX, best->ebx);
		kvm_register_write(vcpu, VCPU_REGS_RCX, best->ecx);
		kvm_register_write(vcpu, VCPU_REGS_RDX, best->edx);
	}
	kvm_x86_ops->skip_emulated_instruction(vcpu);
	trace_kvm_cpuid(function,
			kvm_register_read(vcpu, VCPU_REGS_RAX),
			kvm_register_read(vcpu, VCPU_REGS_RBX),
			kvm_register_read(vcpu, VCPU_REGS_RCX),
			kvm_register_read(vcpu, VCPU_REGS_RDX));
}