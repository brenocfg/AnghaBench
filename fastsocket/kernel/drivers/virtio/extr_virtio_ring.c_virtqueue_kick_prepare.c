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
typedef  scalar_t__ u16 ;
struct TYPE_6__ {TYPE_1__* used; TYPE_2__* avail; } ;
struct vring_virtqueue {TYPE_3__ vring; scalar_t__ event; scalar_t__ num_added; } ;
struct virtqueue {int dummy; } ;
struct TYPE_5__ {scalar_t__ idx; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  END_USE (struct vring_virtqueue*) ; 
 int /*<<< orphan*/  START_USE (struct vring_virtqueue*) ; 
 int VRING_USED_F_NO_NOTIFY ; 
 struct vring_virtqueue* to_vvq (struct virtqueue*) ; 
 int /*<<< orphan*/  virtio_mb () ; 
 int /*<<< orphan*/  virtio_wmb () ; 
 int /*<<< orphan*/  vring_avail_event (TYPE_3__*) ; 
 int vring_need_event (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

bool virtqueue_kick_prepare(struct virtqueue *_vq)
{
	struct vring_virtqueue *vq = to_vvq(_vq);
	u16 new, old;
	bool needs_kick;

	START_USE(vq);
	/* Descriptors and available array need to be set before we expose the
	 * new available array entries. */
	virtio_wmb();

	old = vq->vring.avail->idx;
	new = vq->vring.avail->idx = old + vq->num_added;
	vq->num_added = 0;

	/* Need to update avail index before checking if we should notify */
	virtio_mb();

	if (vq->event) {
		needs_kick = vring_need_event(vring_avail_event(&vq->vring),
					      new, old);
	} else {
		needs_kick = !(vq->vring.used->flags & VRING_USED_F_NO_NOTIFY);
	}
	END_USE(vq);
	return needs_kick;
}