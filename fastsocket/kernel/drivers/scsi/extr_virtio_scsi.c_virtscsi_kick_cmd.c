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
struct virtio_scsi_vq {int /*<<< orphan*/  vq; int /*<<< orphan*/  vq_lock; } ;
struct virtio_scsi_target_state {int /*<<< orphan*/  tgt_lock; int /*<<< orphan*/  sg; } ;
struct virtio_scsi_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int virtqueue_add_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,struct virtio_scsi_cmd*) ; 
 int virtqueue_kick_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_notify (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtscsi_map_cmd (struct virtio_scsi_target_state*,struct virtio_scsi_cmd*,unsigned int*,unsigned int*,size_t,size_t) ; 

__attribute__((used)) static int virtscsi_kick_cmd(struct virtio_scsi_target_state *tgt,
			     struct virtio_scsi_vq *vq,
			     struct virtio_scsi_cmd *cmd,
			     size_t req_size, size_t resp_size)
{
	unsigned int out_num, in_num;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&tgt->tgt_lock, flags);
	virtscsi_map_cmd(tgt, cmd, &out_num, &in_num, req_size, resp_size);

	spin_lock(&vq->vq_lock);
	ret = virtqueue_add_buf(vq->vq, tgt->sg, out_num, in_num, cmd);
	spin_unlock(&tgt->tgt_lock);
	if (ret >= 0)
		ret = virtqueue_kick_prepare(vq->vq);

	spin_unlock_irqrestore(&vq->vq_lock, flags);

	if (ret > 0)
		virtqueue_notify(vq->vq);
	return ret;
}