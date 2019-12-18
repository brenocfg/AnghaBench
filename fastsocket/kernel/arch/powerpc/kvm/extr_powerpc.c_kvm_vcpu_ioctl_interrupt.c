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
struct TYPE_2__ {int /*<<< orphan*/  halt_wakeup; } ;
struct kvm_vcpu {TYPE_1__ stat; int /*<<< orphan*/  wq; } ;
struct kvm_interrupt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvmppc_core_queue_external (struct kvm_vcpu*,struct kvm_interrupt*) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

int kvm_vcpu_ioctl_interrupt(struct kvm_vcpu *vcpu, struct kvm_interrupt *irq)
{
	kvmppc_core_queue_external(vcpu, irq);

	if (waitqueue_active(&vcpu->wq)) {
		wake_up_interruptible(&vcpu->wq);
		vcpu->stat.halt_wakeup++;
	}

	return 0;
}