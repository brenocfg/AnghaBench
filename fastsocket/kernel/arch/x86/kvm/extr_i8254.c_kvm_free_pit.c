#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* vpit; } ;
struct kvm {TYPE_3__ arch; } ;
struct hrtimer {int dummy; } ;
struct TYPE_5__ {struct hrtimer timer; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_1__ pit_timer; int /*<<< orphan*/  irq_ack_notifier; } ;
struct TYPE_8__ {int /*<<< orphan*/  wq; TYPE_2__ pit_state; int /*<<< orphan*/  irq_source_id; int /*<<< orphan*/  expired; int /*<<< orphan*/  mask_notifier; int /*<<< orphan*/  speaker_dev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_PIO_BUS ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_cancel (struct hrtimer*) ; 
 int /*<<< orphan*/  kfree (TYPE_4__*) ; 
 int /*<<< orphan*/  kvm_free_irq_source_id (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_io_bus_unregister_dev (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_unregister_irq_ack_notifier (struct kvm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_unregister_irq_mask_notifier (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void kvm_free_pit(struct kvm *kvm)
{
	struct hrtimer *timer;

	if (kvm->arch.vpit) {
		kvm_io_bus_unregister_dev(kvm, KVM_PIO_BUS, &kvm->arch.vpit->dev);
		kvm_io_bus_unregister_dev(kvm, KVM_PIO_BUS,
					      &kvm->arch.vpit->speaker_dev);
		kvm_unregister_irq_mask_notifier(kvm, 0,
					       &kvm->arch.vpit->mask_notifier);
		kvm_unregister_irq_ack_notifier(kvm,
				&kvm->arch.vpit->pit_state.irq_ack_notifier);
		mutex_lock(&kvm->arch.vpit->pit_state.lock);
		timer = &kvm->arch.vpit->pit_state.pit_timer.timer;
		hrtimer_cancel(timer);
		cancel_work_sync(&kvm->arch.vpit->expired);
		kvm_free_irq_source_id(kvm, kvm->arch.vpit->irq_source_id);
		mutex_unlock(&kvm->arch.vpit->pit_state.lock);
		destroy_workqueue(kvm->arch.vpit->wq);
		kfree(kvm->arch.vpit);
	}
}