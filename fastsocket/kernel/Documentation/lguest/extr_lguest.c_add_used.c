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
struct vring_used_elem {unsigned int id; int len; } ;
struct TYPE_4__ {size_t num; TYPE_1__* used; } ;
struct virtqueue {int /*<<< orphan*/  pending_used; TYPE_2__ vring; } ;
struct TYPE_3__ {size_t idx; struct vring_used_elem* ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void add_used(struct virtqueue *vq, unsigned int head, int len)
{
	struct vring_used_elem *used;

	/*
	 * The virtqueue contains a ring of used buffers.  Get a pointer to the
	 * next entry in that used ring.
	 */
	used = &vq->vring.used->ring[vq->vring.used->idx % vq->vring.num];
	used->id = head;
	used->len = len;
	/* Make sure buffer is written before we update index. */
	wmb();
	vq->vring.used->idx++;
	vq->pending_used++;
}