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
struct kvm_coalesced_mmio_zone {int dummy; } ;
struct kvm_coalesced_mmio_dev {size_t nb_zones; struct kvm_coalesced_mmio_zone* zone; } ;
struct kvm {int /*<<< orphan*/  slots_lock; struct kvm_coalesced_mmio_dev* coalesced_mmio_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 size_t KVM_COALESCED_MMIO_ZONE_MAX ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int kvm_vm_ioctl_register_coalesced_mmio(struct kvm *kvm,
				         struct kvm_coalesced_mmio_zone *zone)
{
	struct kvm_coalesced_mmio_dev *dev = kvm->coalesced_mmio_dev;

	if (dev == NULL)
		return -EINVAL;

	mutex_lock(&kvm->slots_lock);
	if (dev->nb_zones >= KVM_COALESCED_MMIO_ZONE_MAX) {
		mutex_unlock(&kvm->slots_lock);
		return -ENOBUFS;
	}

	dev->zone[dev->nb_zones] = *zone;
	dev->nb_zones++;

	mutex_unlock(&kvm->slots_lock);
	return 0;
}