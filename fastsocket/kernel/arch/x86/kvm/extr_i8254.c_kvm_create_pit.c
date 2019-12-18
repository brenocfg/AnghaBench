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
typedef  int u32 ;
struct TYPE_7__ {int /*<<< orphan*/  func; } ;
struct TYPE_6__ {int reinject; int /*<<< orphan*/  timer; } ;
struct TYPE_8__ {int /*<<< orphan*/  irq_acked; scalar_t__ gsi; } ;
struct kvm_kpit_state {int /*<<< orphan*/  lock; TYPE_2__ pit_timer; TYPE_4__ irq_ack_notifier; struct kvm_pit* pit; int /*<<< orphan*/  inject_lock; } ;
struct kvm_pit {scalar_t__ irq_source_id; int /*<<< orphan*/  dev; int /*<<< orphan*/  speaker_dev; TYPE_3__ mask_notifier; struct kvm_kpit_state pit_state; struct kvm* kvm; int /*<<< orphan*/  expired; int /*<<< orphan*/  wq; } ;
struct TYPE_5__ {struct kvm_pit* vpit; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KVM_PIO_BUS ; 
 int KVM_PIT_SPEAKER_DUMMY ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  hrtimer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct kvm_pit*) ; 
 int /*<<< orphan*/  kvm_free_irq_source_id (struct kvm*,scalar_t__) ; 
 int kvm_io_bus_register_dev (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_io_bus_unregister_dev (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_iodevice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_pit_ack_irq ; 
 int /*<<< orphan*/  kvm_pit_reset (struct kvm_pit*) ; 
 int /*<<< orphan*/  kvm_register_irq_ack_notifier (struct kvm*,TYPE_4__*) ; 
 int /*<<< orphan*/  kvm_register_irq_mask_notifier (struct kvm*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ kvm_request_irq_source_id (struct kvm*) ; 
 struct kvm_pit* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pit_dev_ops ; 
 int /*<<< orphan*/  pit_do_work ; 
 int /*<<< orphan*/  pit_mask_notifer ; 
 int /*<<< orphan*/  speaker_dev_ops ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct kvm_pit *kvm_create_pit(struct kvm *kvm, u32 flags)
{
	struct kvm_pit *pit;
	struct kvm_kpit_state *pit_state;
	int ret;

	pit = kzalloc(sizeof(struct kvm_pit), GFP_KERNEL);
	if (!pit)
		return NULL;

	pit->irq_source_id = kvm_request_irq_source_id(kvm);
	if (pit->irq_source_id < 0) {
		kfree(pit);
		return NULL;
	}

	mutex_init(&pit->pit_state.lock);
	mutex_lock(&pit->pit_state.lock);
	spin_lock_init(&pit->pit_state.inject_lock);

	pit->wq = create_singlethread_workqueue("kvm-pit-wq");
	if (!pit->wq) {
		kfree(pit);
		return NULL;
	}
	INIT_WORK(&pit->expired, pit_do_work);

	kvm->arch.vpit = pit;
	pit->kvm = kvm;

	pit_state = &pit->pit_state;
	pit_state->pit = pit;
	hrtimer_init(&pit_state->pit_timer.timer,
		     CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	pit_state->irq_ack_notifier.gsi = 0;
	pit_state->irq_ack_notifier.irq_acked = kvm_pit_ack_irq;
	kvm_register_irq_ack_notifier(kvm, &pit_state->irq_ack_notifier);
	pit_state->pit_timer.reinject = true;
	mutex_unlock(&pit->pit_state.lock);

	kvm_pit_reset(pit);

	pit->mask_notifier.func = pit_mask_notifer;
	kvm_register_irq_mask_notifier(kvm, 0, &pit->mask_notifier);

	kvm_iodevice_init(&pit->dev, &pit_dev_ops);
	ret = kvm_io_bus_register_dev(kvm, KVM_PIO_BUS, &pit->dev);
	if (ret < 0)
		goto fail;

	if (flags & KVM_PIT_SPEAKER_DUMMY) {
		kvm_iodevice_init(&pit->speaker_dev, &speaker_dev_ops);
		ret = kvm_io_bus_register_dev(kvm, KVM_PIO_BUS,
						&pit->speaker_dev);
		if (ret < 0)
			goto fail_unregister;
	}

	return pit;

fail_unregister:
	kvm_io_bus_unregister_dev(kvm, KVM_PIO_BUS, &pit->dev);

fail:
	if (pit->irq_source_id >= 0)
		kvm_free_irq_source_id(kvm, pit->irq_source_id);

	kfree(pit);
	return NULL;
}