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
struct virtqueue {int dummy; } ;
struct virtio_scsi_vq {struct virtqueue* vq; int /*<<< orphan*/  vq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void virtscsi_init_vq(struct virtio_scsi_vq *virtscsi_vq,
			     struct virtqueue *vq)
{
	spin_lock_init(&virtscsi_vq->vq_lock);
	virtscsi_vq->vq = vq;
}