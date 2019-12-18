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
struct virtqueue {struct virtio_pci_vq_info* priv; int /*<<< orphan*/  vdev; } ;
struct virtio_pci_vq_info {int /*<<< orphan*/  queue_index; } ;
struct virtio_pci_device {scalar_t__ ioaddr; } ;

/* Variables and functions */
 scalar_t__ VIRTIO_PCI_QUEUE_NOTIFY ; 
 int /*<<< orphan*/  iowrite16 (int /*<<< orphan*/ ,scalar_t__) ; 
 struct virtio_pci_device* to_vp_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vp_notify(struct virtqueue *vq)
{
	struct virtio_pci_device *vp_dev = to_vp_device(vq->vdev);
	struct virtio_pci_vq_info *info = vq->priv;

	/* we write the queue's selector into the notification register to
	 * signal the other end */
	iowrite16(info->queue_index, vp_dev->ioaddr + VIRTIO_PCI_QUEUE_NOTIFY);
}