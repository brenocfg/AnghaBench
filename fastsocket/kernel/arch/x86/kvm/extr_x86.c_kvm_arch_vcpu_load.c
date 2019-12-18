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
struct TYPE_3__ {int tsc_offset_adjustment; int last_host_tsc; int tsc_catchup; } ;
struct kvm_vcpu {int cpu; int /*<<< orphan*/  requests; TYPE_1__ arch; } ;
typedef  int s64 ;
struct TYPE_4__ {int /*<<< orphan*/  (* vcpu_load ) (struct kvm_vcpu*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_CLOCK_UPDATE ; 
 int /*<<< orphan*/  KVM_REQ_GLOBAL_CLOCK_UPDATE ; 
 int /*<<< orphan*/  KVM_REQ_STEAL_UPDATE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  accumulate_steal_time (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  adjust_tsc_offset_host (struct kvm_vcpu*,int) ; 
 scalar_t__ check_tsc_unstable () ; 
 int /*<<< orphan*/  kvm_migrate_timers (struct kvm_vcpu*) ; 
 TYPE_2__* kvm_x86_ops ; 
 int native_read_tsc () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int) ; 
 scalar_t__ unlikely (int) ; 

void kvm_arch_vcpu_load(struct kvm_vcpu *vcpu, int cpu)
{
	kvm_x86_ops->vcpu_load(vcpu, cpu);

	/* Apply any externally detected TSC adjustments (due to suspend) */
	if (unlikely(vcpu->arch.tsc_offset_adjustment)) {
		adjust_tsc_offset_host(vcpu, vcpu->arch.tsc_offset_adjustment);
		vcpu->arch.tsc_offset_adjustment = 0;
		set_bit(KVM_REQ_CLOCK_UPDATE, &vcpu->requests);
	}
	if (unlikely(vcpu->cpu != cpu) || check_tsc_unstable()) {
		/* Make sure TSC doesn't go backwards */
		s64 tsc_delta = !vcpu->arch.last_host_tsc ? 0 :
				native_read_tsc() - vcpu->arch.last_host_tsc;
		if (tsc_delta < 0)
			WARN_ON(!check_tsc_unstable());
		if (check_tsc_unstable()) {
			adjust_tsc_offset_host(vcpu, -tsc_delta);
			vcpu->arch.tsc_catchup = 1;
		}
		set_bit(KVM_REQ_GLOBAL_CLOCK_UPDATE, &vcpu->requests);
		if (vcpu->cpu != cpu)
			kvm_migrate_timers(vcpu);
		vcpu->cpu = cpu;
	}

	accumulate_steal_time(vcpu);
	set_bit(KVM_REQ_STEAL_UPDATE, &vcpu->requests);
}