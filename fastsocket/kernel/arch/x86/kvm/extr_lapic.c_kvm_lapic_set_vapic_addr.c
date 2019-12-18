#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* apic; int /*<<< orphan*/  apic_attention; } ;
struct kvm_vcpu {TYPE_2__ arch; int /*<<< orphan*/  kvm; } ;
typedef  scalar_t__ gpa_t ;
struct TYPE_3__ {scalar_t__ vapic_addr; int /*<<< orphan*/  vapic_cache; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KVM_APIC_CHECK_VAPIC ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ kvm_gfn_to_hva_cache_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int offset_in_page (scalar_t__) ; 

int kvm_lapic_set_vapic_addr(struct kvm_vcpu *vcpu, gpa_t vapic_addr)
{
	if (vapic_addr) {
		if (offset_in_page(vapic_addr) > PAGE_SIZE - 4)
			return -EINVAL;

		if (kvm_gfn_to_hva_cache_init(vcpu->kvm,
					      &vcpu->arch.apic->vapic_cache,
					      vapic_addr))
			return -EINVAL;
		__set_bit(KVM_APIC_CHECK_VAPIC, &vcpu->arch.apic_attention);
	} else
		__clear_bit(KVM_APIC_CHECK_VAPIC, &vcpu->arch.apic_attention);

	vcpu->arch.apic->vapic_addr = vapic_addr;
	return 0;
}