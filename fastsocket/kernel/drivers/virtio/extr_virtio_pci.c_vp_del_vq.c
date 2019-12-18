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
struct virtio_pci_vq_info {int /*<<< orphan*/  queue; int /*<<< orphan*/  num; int /*<<< orphan*/  queue_index; int /*<<< orphan*/  node; } ;
struct virtio_pci_device {scalar_t__ ioaddr; scalar_t__ msix_enabled; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned long PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIRTIO_MSI_NO_VECTOR ; 
 scalar_t__ VIRTIO_MSI_QUEUE_VECTOR ; 
 scalar_t__ VIRTIO_PCI_ISR ; 
 scalar_t__ VIRTIO_PCI_QUEUE_PFN ; 
 scalar_t__ VIRTIO_PCI_QUEUE_SEL ; 
 int /*<<< orphan*/  VIRTIO_PCI_VRING_ALIGN ; 
 int /*<<< orphan*/  free_pages_exact (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite16 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct virtio_pci_vq_info*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct virtio_pci_device* to_vp_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vring_del_virtqueue (struct virtqueue*) ; 
 int /*<<< orphan*/  vring_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vp_del_vq(struct virtqueue *vq)
{
	struct virtio_pci_device *vp_dev = to_vp_device(vq->vdev);
	struct virtio_pci_vq_info *info = vq->priv;
	unsigned long flags, size;

	spin_lock_irqsave(&vp_dev->lock, flags);
	list_del(&info->node);
	spin_unlock_irqrestore(&vp_dev->lock, flags);

	iowrite16(info->queue_index, vp_dev->ioaddr + VIRTIO_PCI_QUEUE_SEL);

	if (vp_dev->msix_enabled) {
		iowrite16(VIRTIO_MSI_NO_VECTOR,
			  vp_dev->ioaddr + VIRTIO_MSI_QUEUE_VECTOR);
		/* Flush the write out to device */
		ioread8(vp_dev->ioaddr + VIRTIO_PCI_ISR);
	}

	vring_del_virtqueue(vq);

	/* Select and deactivate the queue */
	iowrite32(0, vp_dev->ioaddr + VIRTIO_PCI_QUEUE_PFN);

	size = PAGE_ALIGN(vring_size(info->num, VIRTIO_PCI_VRING_ALIGN));
	free_pages_exact(info->queue, size);
	kfree(info);
}