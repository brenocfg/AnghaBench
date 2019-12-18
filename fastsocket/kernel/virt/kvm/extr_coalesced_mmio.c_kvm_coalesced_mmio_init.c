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
struct kvm_coalesced_mmio_dev {int /*<<< orphan*/  dev; struct kvm* kvm; int /*<<< orphan*/  lock; } ;
struct kvm {int /*<<< orphan*/  slots_lock; struct kvm_coalesced_mmio_dev* coalesced_mmio_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KVM_MMIO_BUS ; 
 int /*<<< orphan*/  coalesced_mmio_ops ; 
 int /*<<< orphan*/  kfree (struct kvm_coalesced_mmio_dev*) ; 
 int kvm_io_bus_register_dev (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_iodevice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct kvm_coalesced_mmio_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int kvm_coalesced_mmio_init(struct kvm *kvm)
{
	struct kvm_coalesced_mmio_dev *dev;
	int ret;

	dev = kzalloc(sizeof(struct kvm_coalesced_mmio_dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;
	spin_lock_init(&dev->lock);
	kvm_iodevice_init(&dev->dev, &coalesced_mmio_ops);
	dev->kvm = kvm;
	kvm->coalesced_mmio_dev = dev;

	mutex_lock(&kvm->slots_lock);
	ret = kvm_io_bus_register_dev(kvm, KVM_MMIO_BUS, &dev->dev);
	mutex_unlock(&kvm->slots_lock);
	if (ret < 0)
		kfree(dev);

	return ret;
}