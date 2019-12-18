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
struct TYPE_4__ {TYPE_1__* desc; } ;
struct vring_virtqueue {unsigned int free_head; int /*<<< orphan*/  num_free; TYPE_2__ vring; int /*<<< orphan*/ ** data; } ;
struct TYPE_3__ {int flags; unsigned int next; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int VRING_DESC_F_INDIRECT ; 
 int VRING_DESC_F_NEXT ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phys_to_virt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void detach_buf(struct vring_virtqueue *vq, unsigned int head)
{
	unsigned int i;

	/* Clear data ptr. */
	vq->data[head] = NULL;

	/* Put back on free list: find end */
	i = head;

	/* Free the indirect table */
	if (vq->vring.desc[i].flags & VRING_DESC_F_INDIRECT)
		kfree(phys_to_virt(vq->vring.desc[i].addr));

	while (vq->vring.desc[i].flags & VRING_DESC_F_NEXT) {
		i = vq->vring.desc[i].next;
		vq->num_free++;
	}

	vq->vring.desc[i].next = vq->free_head;
	vq->free_head = head;
	/* Plus final descriptor */
	vq->num_free++;
}