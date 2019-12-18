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
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  emulator_write_phys (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  is_long_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_pae (struct kvm_vcpu*) ; 
 int mmu_topup_memory_caches (struct kvm_vcpu*) ; 

__attribute__((used)) static int kvm_pv_mmu_write(struct kvm_vcpu *vcpu,
			     gpa_t addr, gpa_t value)
{
	int bytes = 8;
	int r;

	if (!is_long_mode(vcpu) && !is_pae(vcpu))
		bytes = 4;

	r = mmu_topup_memory_caches(vcpu);
	if (r)
		return r;

	if (!emulator_write_phys(vcpu, addr, &value, bytes))
		return -EFAULT;

	return 1;
}