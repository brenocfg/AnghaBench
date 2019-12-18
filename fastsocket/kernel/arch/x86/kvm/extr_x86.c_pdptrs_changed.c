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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {unsigned int cr3; int /*<<< orphan*/  pdptrs; int /*<<< orphan*/  regs_avail; } ;
struct kvm_vcpu {TYPE_1__ arch; int /*<<< orphan*/  kvm; } ;
typedef  int /*<<< orphan*/  pdpte ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCPU_EXREG_PDPTR ; 
 scalar_t__ is_long_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_pae (struct kvm_vcpu*) ; 
 int kvm_read_guest (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static bool pdptrs_changed(struct kvm_vcpu *vcpu)
{
	u64 pdpte[ARRAY_SIZE(vcpu->arch.pdptrs)];
	bool changed = true;
	int r;

	if (is_long_mode(vcpu) || !is_pae(vcpu))
		return false;

	if (!test_bit(VCPU_EXREG_PDPTR,
		      (unsigned long *)&vcpu->arch.regs_avail))
		return true;

	r = kvm_read_guest(vcpu->kvm, vcpu->arch.cr3 & ~31u, pdpte, sizeof(pdpte));
	if (r < 0)
		goto out;
	changed = memcmp(pdpte, vcpu->arch.pdptrs, sizeof(pdpte)) != 0;
out:

	return changed;
}