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
struct virtio_device {TYPE_1__* config; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* del_vqs ) (struct virtio_device*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int hwrng_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random_recv_done ; 
 int /*<<< orphan*/  register_buffer () ; 
 int /*<<< orphan*/  stub1 (struct virtio_device*) ; 
 int /*<<< orphan*/ * virtio_find_single_vq (struct virtio_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  virtio_hwrng ; 
 int /*<<< orphan*/ * vq ; 

__attribute__((used)) static int probe_common(struct virtio_device *vdev)
{
	int err;

	if (vq) {
		/* We only support one device for now */
		return -EBUSY;
	}
	/* We expect a single virtqueue. */
	vq = virtio_find_single_vq(vdev, random_recv_done, "input");
	if (IS_ERR(vq)) {
		err = PTR_ERR(vq);
		vq = NULL;
		return err;
	}

	err = hwrng_register(&virtio_hwrng);
	if (err) {
		vdev->config->del_vqs(vdev);
		vq = NULL;
		return err;
	}

	register_buffer();
	return 0;
}