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
typedef  int /*<<< orphan*/  uint64_t ;
struct vpd {int /*<<< orphan*/ * irr; } ;
struct TYPE_2__ {int irq_new_pending; int /*<<< orphan*/  vpd; } ;
struct kvm_vcpu {TYPE_1__ arch; int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_vcpu_kick (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vpd* to_host (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __apic_accept_irq(struct kvm_vcpu *vcpu, uint64_t vector)
{
	struct vpd *vpd = to_host(vcpu->kvm, vcpu->arch.vpd);

	if (!test_and_set_bit(vector, &vpd->irr[0])) {
		vcpu->arch.irq_new_pending = 1;
		kvm_vcpu_kick(vcpu);
		return 1;
	}
	return 0;
}