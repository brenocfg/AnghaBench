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
struct TYPE_2__ {scalar_t__ ptc_g_count; } ;
struct kvm_vcpu {TYPE_1__ arch; int /*<<< orphan*/  requests; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_PTC_G ; 
 int /*<<< orphan*/  KVM_REQ_RESUME ; 
 int /*<<< orphan*/  KVM_REQ_TLB_FLUSH ; 
 int /*<<< orphan*/  ptc_ga_remote_func (struct kvm_vcpu*,scalar_t__) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thash_purge_all (struct kvm_vcpu*) ; 
 scalar_t__ unlikely (scalar_t__) ; 
 int /*<<< orphan*/  vcpu_do_resume (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmm_sanity_check (struct kvm_vcpu*) ; 

__attribute__((used)) static void kvm_do_resume_op(struct kvm_vcpu *vcpu)
{
	vmm_sanity_check(vcpu); /*Guarantee vcpu runing on healthy vmm!*/

	if (test_and_clear_bit(KVM_REQ_RESUME, &vcpu->requests)) {
		vcpu_do_resume(vcpu);
		return;
	}

	if (unlikely(test_and_clear_bit(KVM_REQ_TLB_FLUSH, &vcpu->requests))) {
		thash_purge_all(vcpu);
		return;
	}

	if (test_and_clear_bit(KVM_REQ_PTC_G, &vcpu->requests)) {
		while (vcpu->arch.ptc_g_count > 0)
			ptc_ga_remote_func(vcpu, --vcpu->arch.ptc_g_count);
	}
}