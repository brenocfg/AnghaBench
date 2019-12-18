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
struct virtqueue {struct lguest_vq_info* priv; } ;
struct virtio_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  num; scalar_t__ pfn; } ;
struct lguest_vq_info {int /*<<< orphan*/  pages; TYPE_1__ config; } ;
struct lguest_device {TYPE_2__* desc; } ;
struct TYPE_4__ {unsigned int num_vq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int ENOMEM ; 
 struct virtqueue* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  LGUEST_VRING_ALIGN ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct lguest_vq_info*) ; 
 struct lguest_vq_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lg_notify ; 
 unsigned int lg_vq (TYPE_2__*) ; 
 int /*<<< orphan*/  lguest_map (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lguest_setup_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lguest_unmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,unsigned int,int) ; 
 int /*<<< orphan*/  printk (char*,unsigned int,unsigned long) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct virtqueue*) ; 
 struct lguest_device* to_lgdev (struct virtio_device*) ; 
 int /*<<< orphan*/  vring_del_virtqueue (struct virtqueue*) ; 
 int /*<<< orphan*/  vring_interrupt ; 
 struct virtqueue* vring_new_virtqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct virtio_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (struct virtqueue*),char const*) ; 
 int /*<<< orphan*/  vring_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct virtqueue *lg_find_vq(struct virtio_device *vdev,
				    unsigned index,
				    void (*callback)(struct virtqueue *vq),
				    const char *name)
{
	struct lguest_device *ldev = to_lgdev(vdev);
	struct lguest_vq_info *lvq;
	struct virtqueue *vq;
	int err;

	/* We must have this many virtqueues. */
	if (index >= ldev->desc->num_vq)
		return ERR_PTR(-ENOENT);

	lvq = kmalloc(sizeof(*lvq), GFP_KERNEL);
	if (!lvq)
		return ERR_PTR(-ENOMEM);

	/*
	 * Make a copy of the "struct lguest_vqconfig" entry, which sits after
	 * the descriptor.  We need a copy because the config space might not
	 * be aligned correctly.
	 */
	memcpy(&lvq->config, lg_vq(ldev->desc)+index, sizeof(lvq->config));

	printk("Mapping virtqueue %i addr %lx\n", index,
	       (unsigned long)lvq->config.pfn << PAGE_SHIFT);
	/* Figure out how many pages the ring will take, and map that memory */
	lvq->pages = lguest_map((unsigned long)lvq->config.pfn << PAGE_SHIFT,
				DIV_ROUND_UP(vring_size(lvq->config.num,
							LGUEST_VRING_ALIGN),
					     PAGE_SIZE));
	if (!lvq->pages) {
		err = -ENOMEM;
		goto free_lvq;
	}

	/*
	 * OK, tell virtio_ring.c to set up a virtqueue now we know its size
	 * and we've got a pointer to its pages.
	 */
	vq = vring_new_virtqueue(lvq->config.num, LGUEST_VRING_ALIGN,
				 vdev, lvq->pages, lg_notify, callback, name);
	if (!vq) {
		err = -ENOMEM;
		goto unmap;
	}

	/* Make sure the interrupt is allocated. */
	lguest_setup_irq(lvq->config.irq);

	/*
	 * Tell the interrupt for this virtqueue to go to the virtio_ring
	 * interrupt handler.
	 *
	 * FIXME: We used to have a flag for the Host to tell us we could use
	 * the interrupt as a source of randomness: it'd be nice to have that
	 * back.
	 */
	err = request_irq(lvq->config.irq, vring_interrupt, IRQF_SHARED,
			  dev_name(&vdev->dev), vq);
	if (err)
		goto destroy_vring;

	/*
	 * Last of all we hook up our 'struct lguest_vq_info" to the
	 * virtqueue's priv pointer.
	 */
	vq->priv = lvq;
	return vq;

destroy_vring:
	vring_del_virtqueue(vq);
unmap:
	lguest_unmap(lvq->pages);
free_lvq:
	kfree(lvq);
	return ERR_PTR(err);
}