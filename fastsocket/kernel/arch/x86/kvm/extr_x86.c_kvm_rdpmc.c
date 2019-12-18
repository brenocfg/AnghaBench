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
typedef  int u32 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_REGS_RAX ; 
 int /*<<< orphan*/  VCPU_REGS_RCX ; 
 int /*<<< orphan*/  VCPU_REGS_RDX ; 
 int kvm_pmu_read_pmc (struct kvm_vcpu*,int,int*) ; 
 int kvm_register_read (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_register_write (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 

bool kvm_rdpmc(struct kvm_vcpu *vcpu)
{
	u32 ecx = kvm_register_read(vcpu, VCPU_REGS_RCX);
	u64 data;
	int err;

	err = kvm_pmu_read_pmc(vcpu, ecx, &data);
	if (err)
		return err;
	kvm_register_write(vcpu, VCPU_REGS_RAX, (u32)data);
	kvm_register_write(vcpu, VCPU_REGS_RDX, data >> 32);
	return err;
}