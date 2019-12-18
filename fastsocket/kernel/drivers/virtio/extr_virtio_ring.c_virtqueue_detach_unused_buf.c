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
struct TYPE_4__ {unsigned int num; TYPE_1__* avail; } ;
struct vring_virtqueue {unsigned int num_free; TYPE_2__ vring; void** data; } ;
struct virtqueue {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  END_USE (struct vring_virtqueue*) ; 
 int /*<<< orphan*/  START_USE (struct vring_virtqueue*) ; 
 int /*<<< orphan*/  detach_buf (struct vring_virtqueue*,unsigned int) ; 
 struct vring_virtqueue* to_vvq (struct virtqueue*) ; 

void *virtqueue_detach_unused_buf(struct virtqueue *_vq)
{
	struct vring_virtqueue *vq = to_vvq(_vq);
	unsigned int i;
	void *buf;

	START_USE(vq);

	for (i = 0; i < vq->vring.num; i++) {
		if (!vq->data[i])
			continue;
		/* detach_buf clears data, so grab it now. */
		buf = vq->data[i];
		detach_buf(vq, i);
		vq->vring.avail->idx--;
		END_USE(vq);
		return buf;
	}
	/* That should have freed everything. */
	BUG_ON(vq->num_free != vq->vring.num);

	END_USE(vq);
	return NULL;
}