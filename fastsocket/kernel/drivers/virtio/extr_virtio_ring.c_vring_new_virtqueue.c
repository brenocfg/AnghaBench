#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct virtqueue {void (* callback ) (struct virtqueue*) ;char const* name; int /*<<< orphan*/  list; struct virtio_device* vdev; } ;
struct TYPE_6__ {TYPE_2__* desc; TYPE_1__* avail; } ;
struct vring_virtqueue {void (* notify ) (struct virtqueue*) ;int broken; int in_use; unsigned int num_free; struct virtqueue vq; int /*<<< orphan*/ ** data; TYPE_3__ vring; scalar_t__ free_head; void* event; void* indirect; scalar_t__ num_added; scalar_t__ last_used_idx; } ;
struct virtio_device {int /*<<< orphan*/  vqs; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {unsigned int next; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VIRTIO_RING_F_EVENT_IDX ; 
 int /*<<< orphan*/  VIRTIO_RING_F_INDIRECT_DESC ; 
 int /*<<< orphan*/  VRING_AVAIL_F_NO_INTERRUPT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,unsigned int) ; 
 struct vring_virtqueue* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* virtio_has_feature (struct virtio_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vring_init (TYPE_3__*,unsigned int,void*,unsigned int) ; 

struct virtqueue *vring_new_virtqueue(unsigned int num,
				      unsigned int vring_align,
				      struct virtio_device *vdev,
				      void *pages,
				      void (*notify)(struct virtqueue *),
				      void (*callback)(struct virtqueue *),
				      const char *name)
{
	struct vring_virtqueue *vq;
	unsigned int i;

	/* We assume num is a power of 2. */
	if (num & (num - 1)) {
		dev_warn(&vdev->dev, "Bad virtqueue length %u\n", num);
		return NULL;
	}

	vq = kmalloc(sizeof(*vq) + sizeof(void *)*num, GFP_KERNEL);
	if (!vq)
		return NULL;

	vring_init(&vq->vring, num, pages, vring_align);
	vq->vq.callback = callback;
	vq->vq.vdev = vdev;
	vq->vq.name = name;
	vq->notify = notify;
	vq->broken = false;
	vq->last_used_idx = 0;
	vq->num_added = 0;
	list_add_tail(&vq->vq.list, &vdev->vqs);
#ifdef DEBUG
	vq->in_use = false;
#endif

	vq->indirect = virtio_has_feature(vdev, VIRTIO_RING_F_INDIRECT_DESC);
	vq->event = virtio_has_feature(vdev, VIRTIO_RING_F_EVENT_IDX);

	/* No callback?  Tell other side not to bother us. */
	if (!callback)
		vq->vring.avail->flags |= VRING_AVAIL_F_NO_INTERRUPT;

	/* Put everything in free lists. */
	vq->num_free = num;
	vq->free_head = 0;
	for (i = 0; i < num-1; i++) {
		vq->vring.desc[i].next = i+1;
		vq->data[i] = NULL;
	}
	vq->data[i] = NULL;

	return &vq->vq;
}