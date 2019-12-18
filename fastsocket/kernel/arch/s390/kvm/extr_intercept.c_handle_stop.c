#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int action_bits; int /*<<< orphan*/  lock; } ;
struct TYPE_10__ {TYPE_4__ local_int; TYPE_2__* sie_block; } ;
struct TYPE_6__ {int /*<<< orphan*/  exit_stop_request; } ;
struct kvm_vcpu {TYPE_5__ arch; TYPE_3__* run; TYPE_1__ stat; } ;
struct TYPE_8__ {int /*<<< orphan*/  exit_reason; } ;
struct TYPE_7__ {int /*<<< orphan*/  cpuflags; } ;

/* Variables and functions */
 int ACTION_RELOADVCPU_ON_STOP ; 
 int ACTION_STOP_ON_STOP ; 
 int ACTION_STORE_ON_STOP ; 
 int /*<<< orphan*/  CPUSTAT_RUNNING ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  KVM_EXIT_INTR ; 
 int /*<<< orphan*/  KVM_S390_STORE_STATUS_NOADDR ; 
 int SIE_INTERCEPT_RERUNVCPU ; 
 int /*<<< orphan*/  VCPU_EVENT (struct kvm_vcpu*,int,char*,char*) ; 
 int __kvm_s390_vcpu_store_status (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_clear_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_stop(struct kvm_vcpu *vcpu)
{
	int rc = 0;

	vcpu->stat.exit_stop_request++;
	atomic_clear_mask(CPUSTAT_RUNNING, &vcpu->arch.sie_block->cpuflags);
	spin_lock_bh(&vcpu->arch.local_int.lock);
	if (vcpu->arch.local_int.action_bits & ACTION_STORE_ON_STOP) {
		vcpu->arch.local_int.action_bits &= ~ACTION_STORE_ON_STOP;
		rc = __kvm_s390_vcpu_store_status(vcpu,
						  KVM_S390_STORE_STATUS_NOADDR);
		if (rc >= 0)
			rc = -ENOTSUPP;
	}

	if (vcpu->arch.local_int.action_bits & ACTION_RELOADVCPU_ON_STOP) {
		vcpu->arch.local_int.action_bits &= ~ACTION_RELOADVCPU_ON_STOP;
		rc = SIE_INTERCEPT_RERUNVCPU;
		vcpu->run->exit_reason = KVM_EXIT_INTR;
	}

	if (vcpu->arch.local_int.action_bits & ACTION_STOP_ON_STOP) {
		vcpu->arch.local_int.action_bits &= ~ACTION_STOP_ON_STOP;
		VCPU_EVENT(vcpu, 3, "%s", "cpu stopped");
		rc = -ENOTSUPP;
	}

	spin_unlock_bh(&vcpu->arch.local_int.lock);
	return rc;
}