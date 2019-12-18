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
struct virtio_scsi_event_node {int /*<<< orphan*/  event; } ;
struct virtio_scsi_event {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vq_lock; int /*<<< orphan*/  vq; } ;
struct virtio_scsi {TYPE_1__ event_vq; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int virtqueue_add_buf (int /*<<< orphan*/ ,struct scatterlist*,int /*<<< orphan*/ ,int,struct virtio_scsi_event_node*) ; 
 int /*<<< orphan*/  virtqueue_kick (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int virtscsi_kick_event(struct virtio_scsi *vscsi,
			       struct virtio_scsi_event_node *event_node)
{
	int ret;
	struct scatterlist sg;
	unsigned long flags;

	sg_init_one(&sg, &event_node->event, sizeof(struct virtio_scsi_event));

	spin_lock_irqsave(&vscsi->event_vq.vq_lock, flags);

	ret = virtqueue_add_buf(vscsi->event_vq.vq, &sg, 0, 1, event_node);
	if (ret >= 0)
		virtqueue_kick(vscsi->event_vq.vq);

	spin_unlock_irqrestore(&vscsi->event_vq.vq_lock, flags);

	return ret;
}