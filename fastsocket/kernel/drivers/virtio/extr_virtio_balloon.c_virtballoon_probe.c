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
struct virtio_device {TYPE_1__* config; struct virtio_balloon* priv; } ;
struct virtio_balloon {int /*<<< orphan*/  tell_host_first; int /*<<< orphan*/  thread; scalar_t__ need_stats_update; struct virtio_device* vdev; int /*<<< orphan*/  config_change; scalar_t__ num_pages; int /*<<< orphan*/  pages; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* del_vqs ) (struct virtio_device*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIRTIO_BALLOON_F_MUST_TELL_HOST ; 
 int /*<<< orphan*/  balloon ; 
 int init_vqs (struct virtio_balloon*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct virtio_balloon*) ; 
 struct virtio_balloon* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct virtio_balloon*,char*) ; 
 int /*<<< orphan*/  stub1 (struct virtio_device*) ; 
 int /*<<< orphan*/  virtio_has_feature (struct virtio_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int virtballoon_probe(struct virtio_device *vdev)
{
	struct virtio_balloon *vb;
	int err;

	vdev->priv = vb = kmalloc(sizeof(*vb), GFP_KERNEL);
	if (!vb) {
		err = -ENOMEM;
		goto out;
	}

	INIT_LIST_HEAD(&vb->pages);
	vb->num_pages = 0;
	init_waitqueue_head(&vb->config_change);
	vb->vdev = vdev;
	vb->need_stats_update = 0;

	err = init_vqs(vb);
	if (err)
		goto out_free_vb;

	vb->thread = kthread_run(balloon, vb, "vballoon");
	if (IS_ERR(vb->thread)) {
		err = PTR_ERR(vb->thread);
		goto out_del_vqs;
	}

	vb->tell_host_first
		= virtio_has_feature(vdev, VIRTIO_BALLOON_F_MUST_TELL_HOST);

	return 0;

out_del_vqs:
	vdev->config->del_vqs(vdev);
out_free_vb:
	kfree(vb);
out:
	return err;
}