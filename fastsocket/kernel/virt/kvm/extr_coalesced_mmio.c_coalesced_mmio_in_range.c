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
struct kvm_coalesced_mmio_zone {scalar_t__ addr; scalar_t__ size; } ;
struct kvm_coalesced_mmio_ring {int first; int last; } ;
struct kvm_coalesced_mmio_dev {int nb_zones; struct kvm_coalesced_mmio_zone* zone; TYPE_1__* kvm; } ;
typedef  scalar_t__ gpa_t ;
struct TYPE_2__ {struct kvm_coalesced_mmio_ring* coalesced_mmio_ring; } ;

/* Variables and functions */
 int KVM_COALESCED_MMIO_MAX ; 
 unsigned int KVM_MAX_VCPUS ; 

__attribute__((used)) static int coalesced_mmio_in_range(struct kvm_coalesced_mmio_dev *dev,
				   gpa_t addr, int len)
{
	struct kvm_coalesced_mmio_zone *zone;
	struct kvm_coalesced_mmio_ring *ring;
	unsigned avail;
	int i;

	/* Are we able to batch it ? */

	/* last is the first free entry
	 * check if we don't meet the first used entry
	 * there is always one unused entry in the buffer
	 */
	ring = dev->kvm->coalesced_mmio_ring;
	avail = (ring->first - ring->last - 1) % KVM_COALESCED_MMIO_MAX;
	if (avail < KVM_MAX_VCPUS) {
		/* full */
		return 0;
	}

	/* is it in a batchable area ? */

	for (i = 0; i < dev->nb_zones; i++) {
		zone = &dev->zone[i];

		/* (addr,len) is fully included in
		 * (zone->addr, zone->size)
		 */

		if (zone->addr <= addr &&
		    addr + len <= zone->addr + zone->size)
			return 1;
	}
	return 0;
}