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
typedef  size_t u32 ;
struct virtio_scsi {int /*<<< orphan*/ ** tgt; } ;
struct virtio_device {TYPE_1__* config; } ;
struct Scsi_Host {size_t max_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* del_vqs ) (struct virtio_device*) ;int /*<<< orphan*/  (* reset ) (struct virtio_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct virtio_scsi* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  stub1 (struct virtio_device*) ; 
 int /*<<< orphan*/  stub2 (struct virtio_device*) ; 
 struct Scsi_Host* virtio_scsi_host (struct virtio_device*) ; 

__attribute__((used)) static void virtscsi_remove_vqs(struct virtio_device *vdev)
{
	struct Scsi_Host *sh = virtio_scsi_host(vdev);
	struct virtio_scsi *vscsi = shost_priv(sh);
	u32 i, num_targets;

	/* Stop all the virtqueues. */
	vdev->config->reset(vdev);

	num_targets = sh->max_id;
	for (i = 0; i < num_targets; i++) {
		kfree(vscsi->tgt[i]);
		vscsi->tgt[i] = NULL;
	}

	vdev->config->del_vqs(vdev);
}