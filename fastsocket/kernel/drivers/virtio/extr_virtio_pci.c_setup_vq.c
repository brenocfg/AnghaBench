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
typedef  scalar_t__ u16 ;
struct virtqueue {struct virtio_pci_vq_info* priv; } ;
struct virtio_pci_vq_info {unsigned int queue_index; int /*<<< orphan*/ * queue; int /*<<< orphan*/  node; struct virtqueue* vq; scalar_t__ num; scalar_t__ msix_vector; } ;
struct virtio_pci_device {scalar_t__ ioaddr; int /*<<< orphan*/  lock; int /*<<< orphan*/  virtqueues; } ;
struct virtio_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int ENOMEM ; 
 struct virtqueue* ERR_PTR (int) ; 
 int GFP_KERNEL ; 
 unsigned long PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 scalar_t__ VIRTIO_MSI_NO_VECTOR ; 
 scalar_t__ VIRTIO_MSI_QUEUE_VECTOR ; 
 int VIRTIO_PCI_QUEUE_ADDR_SHIFT ; 
 scalar_t__ VIRTIO_PCI_QUEUE_NUM ; 
 scalar_t__ VIRTIO_PCI_QUEUE_PFN ; 
 scalar_t__ VIRTIO_PCI_QUEUE_SEL ; 
 int /*<<< orphan*/  VIRTIO_PCI_VRING_ALIGN ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/ * alloc_pages_exact (unsigned long,int) ; 
 int /*<<< orphan*/  free_pages_exact (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ ioread16 (scalar_t__) ; 
 scalar_t__ ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite16 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct virtio_pci_vq_info*) ; 
 struct virtio_pci_vq_info* kmalloc (int,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct virtio_pci_device* to_vp_device (struct virtio_device*) ; 
 int virt_to_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vp_notify ; 
 int /*<<< orphan*/  vring_del_virtqueue (struct virtqueue*) ; 
 struct virtqueue* vring_new_virtqueue (scalar_t__,int /*<<< orphan*/ ,struct virtio_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (struct virtqueue*),char const*) ; 
 int /*<<< orphan*/  vring_size (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct virtqueue *setup_vq(struct virtio_device *vdev, unsigned index,
				  void (*callback)(struct virtqueue *vq),
				  const char *name,
				  u16 msix_vec)
{
	struct virtio_pci_device *vp_dev = to_vp_device(vdev);
	struct virtio_pci_vq_info *info;
	struct virtqueue *vq;
	unsigned long flags, size;
	u16 num;
	int err;

	/* Select the queue we're interested in */
	iowrite16(index, vp_dev->ioaddr + VIRTIO_PCI_QUEUE_SEL);

	/* Check if queue is either not available or already active. */
	num = ioread16(vp_dev->ioaddr + VIRTIO_PCI_QUEUE_NUM);
	if (!num || ioread32(vp_dev->ioaddr + VIRTIO_PCI_QUEUE_PFN))
		return ERR_PTR(-ENOENT);

	/* allocate and fill out our structure the represents an active
	 * queue */
	info = kmalloc(sizeof(struct virtio_pci_vq_info), GFP_KERNEL);
	if (!info)
		return ERR_PTR(-ENOMEM);

	info->queue_index = index;
	info->num = num;
	info->msix_vector = msix_vec;

	size = PAGE_ALIGN(vring_size(num, VIRTIO_PCI_VRING_ALIGN));
	info->queue = alloc_pages_exact(size, GFP_KERNEL|__GFP_ZERO);
	if (info->queue == NULL) {
		err = -ENOMEM;
		goto out_info;
	}

	/* activate the queue */
	iowrite32(virt_to_phys(info->queue) >> VIRTIO_PCI_QUEUE_ADDR_SHIFT,
		  vp_dev->ioaddr + VIRTIO_PCI_QUEUE_PFN);

	/* create the vring */
	vq = vring_new_virtqueue(info->num, VIRTIO_PCI_VRING_ALIGN,
				 vdev, info->queue, vp_notify, callback, name);
	if (!vq) {
		err = -ENOMEM;
		goto out_activate_queue;
	}

	vq->priv = info;
	info->vq = vq;

	if (msix_vec != VIRTIO_MSI_NO_VECTOR) {
		iowrite16(msix_vec, vp_dev->ioaddr + VIRTIO_MSI_QUEUE_VECTOR);
		msix_vec = ioread16(vp_dev->ioaddr + VIRTIO_MSI_QUEUE_VECTOR);
		if (msix_vec == VIRTIO_MSI_NO_VECTOR) {
			err = -EBUSY;
			goto out_assign;
		}
	}

	spin_lock_irqsave(&vp_dev->lock, flags);
	list_add(&info->node, &vp_dev->virtqueues);
	spin_unlock_irqrestore(&vp_dev->lock, flags);

	return vq;

out_assign:
	vring_del_virtqueue(vq);
out_activate_queue:
	iowrite32(0, vp_dev->ioaddr + VIRTIO_PCI_QUEUE_PFN);
	free_pages_exact(info->queue, size);
out_info:
	kfree(info);
	return ERR_PTR(err);
}