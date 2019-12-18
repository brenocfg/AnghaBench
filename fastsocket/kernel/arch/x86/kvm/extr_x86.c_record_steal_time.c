#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int version; int /*<<< orphan*/  steal; } ;
struct TYPE_5__ {int msr_val; TYPE_3__ steal; int /*<<< orphan*/  stime; scalar_t__ accum_steal; } ;
struct TYPE_6__ {TYPE_1__ st; } ;
struct kvm_vcpu {TYPE_2__ arch; int /*<<< orphan*/  kvm; } ;
struct kvm_steal_time {int dummy; } ;

/* Variables and functions */
 int KVM_MSR_ENABLED ; 
 int /*<<< orphan*/  kvm_read_guest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  kvm_write_guest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void record_steal_time(struct kvm_vcpu *vcpu)
{
	if (!(vcpu->arch.st.msr_val & KVM_MSR_ENABLED))
		return;

	if (unlikely(kvm_read_guest(vcpu->kvm, vcpu->arch.st.stime,
		&vcpu->arch.st.steal, sizeof(struct kvm_steal_time))))
		return;

	vcpu->arch.st.steal.steal += vcpu->arch.st.accum_steal;
	vcpu->arch.st.steal.version += 2;
	vcpu->arch.st.accum_steal = 0;

	kvm_write_guest(vcpu->kvm, vcpu->arch.st.stime,
		&vcpu->arch.st.steal, sizeof(struct kvm_steal_time));
}