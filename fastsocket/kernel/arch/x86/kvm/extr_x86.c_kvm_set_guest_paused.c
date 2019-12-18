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
struct TYPE_2__ {int pvclock_set_guest_stopped_request; int time; int /*<<< orphan*/  pv_time_enabled; } ;
struct kvm_vcpu {int /*<<< orphan*/  requests; TYPE_1__ arch; int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KVM_REQ_CLOCK_UPDATE ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  mark_page_dirty (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvm_set_guest_paused(struct kvm_vcpu *vcpu)
{
	if (!vcpu->arch.pv_time_enabled)
		return -EINVAL;
	vcpu->arch.pvclock_set_guest_stopped_request = true;
	mark_page_dirty(vcpu->kvm, vcpu->arch.time >> PAGE_SHIFT);
	set_bit(KVM_REQ_CLOCK_UPDATE, &vcpu->requests);
	return 0;
}