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
typedef  int u64 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_REGS_RAX ; 
 int /*<<< orphan*/  VCPU_REGS_RDX ; 
 unsigned int kvm_register_read (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 kvm_read_edx_eax(struct kvm_vcpu *vcpu)
{
	return (kvm_register_read(vcpu, VCPU_REGS_RAX) & -1u)
		| ((u64)(kvm_register_read(vcpu, VCPU_REGS_RDX) & -1u) << 32);
}