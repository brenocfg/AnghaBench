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
struct exit_ctl_data {scalar_t__ exit_reason; } ;
struct TYPE_2__ {struct exit_ctl_data exit_data; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ EXIT_REASON_DEBUG ; 
 int /*<<< orphan*/  panic_vm (struct kvm_vcpu*,char*) ; 
 int /*<<< orphan*/  vmm_sanity ; 

__attribute__((used)) static void vmm_sanity_check(struct kvm_vcpu *vcpu)
{
	struct exit_ctl_data *p = &vcpu->arch.exit_data;

	if (!vmm_sanity && p->exit_reason != EXIT_REASON_DEBUG) {
		panic_vm(vcpu, "Failed to do vmm sanity check,"
			"it maybe caused by crashed vmm!!\n\n");
	}
}