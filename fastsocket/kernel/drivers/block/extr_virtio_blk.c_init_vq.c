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
struct virtio_blk {int /*<<< orphan*/  vq; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_done ; 
 int /*<<< orphan*/  virtio_find_single_vq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int init_vq(struct virtio_blk *vblk)
{
	int err = 0;

	/* We expect one virtqueue, for output. */
	vblk->vq = virtio_find_single_vq(vblk->vdev, blk_done, "requests");
	if (IS_ERR(vblk->vq))
		err = PTR_ERR(vblk->vq);

	return err;
}