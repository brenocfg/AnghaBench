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
struct virtqueue {int /*<<< orphan*/  vdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  vq_lock; } ;
struct virtio_scsi {TYPE_1__ event_vq; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 struct virtio_scsi* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct Scsi_Host* virtio_scsi_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtscsi_complete_event ; 
 int /*<<< orphan*/  virtscsi_vq_done (struct virtqueue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void virtscsi_event_done(struct virtqueue *vq)
{
	struct Scsi_Host *sh = virtio_scsi_host(vq->vdev);
	struct virtio_scsi *vscsi = shost_priv(sh);
	unsigned long flags;

	spin_lock_irqsave(&vscsi->event_vq.vq_lock, flags);
	virtscsi_vq_done(vq, virtscsi_complete_event);
	spin_unlock_irqrestore(&vscsi->event_vq.vq_lock, flags);
}