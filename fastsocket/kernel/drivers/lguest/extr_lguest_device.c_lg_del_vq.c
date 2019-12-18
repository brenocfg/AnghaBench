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
struct virtqueue {struct lguest_vq_info* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;
struct lguest_vq_info {int /*<<< orphan*/  pages; TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct virtqueue*) ; 
 int /*<<< orphan*/  kfree (struct lguest_vq_info*) ; 
 int /*<<< orphan*/  lguest_unmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vring_del_virtqueue (struct virtqueue*) ; 

__attribute__((used)) static void lg_del_vq(struct virtqueue *vq)
{
	struct lguest_vq_info *lvq = vq->priv;

	/* Release the interrupt */
	free_irq(lvq->config.irq, vq);
	/* Tell virtio_ring.c to free the virtqueue. */
	vring_del_virtqueue(vq);
	/* Unmap the pages containing the ring. */
	lguest_unmap(lvq->pages);
	/* Free our own queue information. */
	kfree(lvq);
}