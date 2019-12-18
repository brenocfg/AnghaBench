#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kvm_vcpu {int cpu; int /*<<< orphan*/  requests; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_KICK ; 
 scalar_t__ cpu_online (int) ; 
 int get_cpu () ; 
 unsigned int nr_cpu_ids ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  smp_send_reschedule (int) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void kvm_vcpu_kick(struct kvm_vcpu *vcpu)
{
	int me;
	int cpu = vcpu->cpu;

	if (waitqueue_active(&vcpu->wq))
		wake_up_interruptible(&vcpu->wq);

	me = get_cpu();
	if (cpu != me && (unsigned) cpu < nr_cpu_ids && cpu_online(cpu))
		if (!test_and_set_bit(KVM_REQ_KICK, &vcpu->requests))
			smp_send_reschedule(cpu);
	put_cpu();
}