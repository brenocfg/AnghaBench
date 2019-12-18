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
struct virtio_device {struct virtio_blk* priv; } ;
struct virtio_blk {int /*<<< orphan*/  config_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtblk_wq ; 

__attribute__((used)) static void virtblk_config_changed(struct virtio_device *vdev)
{
	struct virtio_blk *vblk = vdev->priv;

	queue_work(virtblk_wq, &vblk->config_work);
}