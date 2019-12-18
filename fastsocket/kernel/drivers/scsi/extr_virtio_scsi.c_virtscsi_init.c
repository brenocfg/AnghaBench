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
typedef  int /*<<< orphan*/  vq_callback_t ;
typedef  int u32 ;
struct virtqueue {int dummy; } ;
struct virtio_scsi {int /*<<< orphan*/ * tgt; int /*<<< orphan*/  req_vq; int /*<<< orphan*/  event_vq; int /*<<< orphan*/  ctrl_vq; } ;
struct virtio_device {TYPE_1__* config; } ;
struct TYPE_2__ {int (* find_vqs ) (struct virtio_device*,int,struct virtqueue**,int /*<<< orphan*/ **,char const**) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  VIRTIO_SCSI_CDB_SIZE ; 
 int /*<<< orphan*/  VIRTIO_SCSI_F_HOTPLUG ; 
 int /*<<< orphan*/  VIRTIO_SCSI_SENSE_SIZE ; 
 int /*<<< orphan*/  cdb_size ; 
 int /*<<< orphan*/  seg_max ; 
 int /*<<< orphan*/  sense_size ; 
 int stub1 (struct virtio_device*,int,struct virtqueue**,int /*<<< orphan*/ **,char const**) ; 
 scalar_t__ virtio_has_feature (struct virtio_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtscsi_alloc_tgt (struct virtio_device*,int) ; 
 scalar_t__ virtscsi_config_get (struct virtio_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtscsi_config_set (struct virtio_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * virtscsi_ctrl_done ; 
 int /*<<< orphan*/ * virtscsi_event_done ; 
 int /*<<< orphan*/  virtscsi_init_vq (int /*<<< orphan*/ *,struct virtqueue*) ; 
 int /*<<< orphan*/  virtscsi_kick_event_all (struct virtio_scsi*) ; 
 int /*<<< orphan*/  virtscsi_remove_vqs (struct virtio_device*) ; 
 int /*<<< orphan*/ * virtscsi_req_done ; 

__attribute__((used)) static int virtscsi_init(struct virtio_device *vdev,
			 struct virtio_scsi *vscsi, int num_targets)
{
	int err;
	struct virtqueue *vqs[3];
	u32 i, sg_elems;

	vq_callback_t *callbacks[] = {
		virtscsi_ctrl_done,
		virtscsi_event_done,
		virtscsi_req_done
	};
	const char *names[] = {
		"control",
		"event",
		"request"
	};

	/* Discover virtqueues and write information to configuration.  */
	err = vdev->config->find_vqs(vdev, 3, vqs, callbacks, names);
	if (err)
		return err;

	virtscsi_init_vq(&vscsi->ctrl_vq, vqs[0]);
	virtscsi_init_vq(&vscsi->event_vq, vqs[1]);
	virtscsi_init_vq(&vscsi->req_vq, vqs[2]);

	virtscsi_config_set(vdev, cdb_size, VIRTIO_SCSI_CDB_SIZE);
	virtscsi_config_set(vdev, sense_size, VIRTIO_SCSI_SENSE_SIZE);

	if (virtio_has_feature(vdev, VIRTIO_SCSI_F_HOTPLUG))
		virtscsi_kick_event_all(vscsi);

	/* We need to know how many segments before we allocate.  */
	sg_elems = virtscsi_config_get(vdev, seg_max) ?: 1;

	for (i = 0; i < num_targets; i++) {
		vscsi->tgt[i] = virtscsi_alloc_tgt(vdev, sg_elems);
		if (!vscsi->tgt[i]) {
			err = -ENOMEM;
			goto out;
		}
	}
	err = 0;

out:
	if (err)
		virtscsi_remove_vqs(vdev);
	return err;
}