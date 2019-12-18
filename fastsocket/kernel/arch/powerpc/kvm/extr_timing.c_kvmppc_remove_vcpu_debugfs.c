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
struct TYPE_2__ {int /*<<< orphan*/ * debugfs_exit_timing; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ *) ; 

void kvmppc_remove_vcpu_debugfs(struct kvm_vcpu *vcpu)
{
	if (vcpu->arch.debugfs_exit_timing) {
		debugfs_remove(vcpu->arch.debugfs_exit_timing);
		vcpu->arch.debugfs_exit_timing = NULL;
	}
}