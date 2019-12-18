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
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int hardware_exit_reason; } ;
struct kvm_run {TYPE_1__ hw; int /*<<< orphan*/  exit_reason; } ;
struct exit_ctl_data {scalar_t__ exit_reason; } ;

/* Variables and functions */
 scalar_t__ EXIT_REASON_SAL_CALL ; 
 int /*<<< orphan*/  KVM_EXIT_UNKNOWN ; 
 struct exit_ctl_data* kvm_get_exit_data (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_sal_emul (struct kvm_vcpu*) ; 

__attribute__((used)) static int handle_sal_call(struct kvm_vcpu *vcpu, struct kvm_run *kvm_run)
{
	struct exit_ctl_data *p;

	p = kvm_get_exit_data(vcpu);

	if (p->exit_reason == EXIT_REASON_SAL_CALL) {
		kvm_sal_emul(vcpu);
		return 1;
	} else {
		kvm_run->exit_reason = KVM_EXIT_UNKNOWN;
		kvm_run->hw.hardware_exit_reason = 3;
		return 0;
	}

}