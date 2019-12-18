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
struct virtqueue {struct kvm_vqconfig* priv; } ;
struct kvm_vqconfig {int /*<<< orphan*/  num; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_S390_VIRTIO_RING_ALIGN ; 
 int /*<<< orphan*/  vmem_remove_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vring_del_virtqueue (struct virtqueue*) ; 
 int /*<<< orphan*/  vring_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_del_vq(struct virtqueue *vq)
{
	struct kvm_vqconfig *config = vq->priv;

	vring_del_virtqueue(vq);
	vmem_remove_mapping(config->address,
			    vring_size(config->num,
				       KVM_S390_VIRTIO_RING_ALIGN));
}