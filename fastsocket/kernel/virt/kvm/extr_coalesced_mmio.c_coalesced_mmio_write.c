#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kvm_io_device {int dummy; } ;
struct kvm_coalesced_mmio_ring {size_t last; TYPE_2__* coalesced_mmio; } ;
struct kvm_coalesced_mmio_dev {int /*<<< orphan*/  lock; TYPE_1__* kvm; } ;
typedef  int /*<<< orphan*/  gpa_t ;
struct TYPE_4__ {int len; int /*<<< orphan*/  data; int /*<<< orphan*/  phys_addr; } ;
struct TYPE_3__ {struct kvm_coalesced_mmio_ring* coalesced_mmio_ring; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int KVM_COALESCED_MMIO_MAX ; 
 int /*<<< orphan*/  coalesced_mmio_in_range (struct kvm_coalesced_mmio_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct kvm_coalesced_mmio_dev* to_mmio (struct kvm_io_device*) ; 

__attribute__((used)) static int coalesced_mmio_write(struct kvm_io_device *this,
				gpa_t addr, int len, const void *val)
{
	struct kvm_coalesced_mmio_dev *dev = to_mmio(this);
	struct kvm_coalesced_mmio_ring *ring = dev->kvm->coalesced_mmio_ring;
	if (!coalesced_mmio_in_range(dev, addr, len))
		return -EOPNOTSUPP;

	spin_lock(&dev->lock);

	/* copy data in first free entry of the ring */

	ring->coalesced_mmio[ring->last].phys_addr = addr;
	ring->coalesced_mmio[ring->last].len = len;
	memcpy(ring->coalesced_mmio[ring->last].data, val, len);
	smp_wmb();
	ring->last = (ring->last + 1) % KVM_COALESCED_MMIO_MAX;
	spin_unlock(&dev->lock);
	return 0;
}