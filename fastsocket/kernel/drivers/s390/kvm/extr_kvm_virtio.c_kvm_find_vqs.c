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
struct virtqueue {int dummy; } ;
struct virtio_device {int dummy; } ;
struct kvm_device {TYPE_1__* desc; } ;
struct TYPE_2__ {unsigned int num_vq; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (struct virtqueue*) ; 
 int PTR_ERR (struct virtqueue*) ; 
 int /*<<< orphan*/  kvm_del_vqs (struct virtio_device*) ; 
 struct virtqueue* kvm_find_vq (struct virtio_device*,int,int /*<<< orphan*/ *,char const*) ; 
 struct kvm_device* to_kvmdev (struct virtio_device*) ; 

__attribute__((used)) static int kvm_find_vqs(struct virtio_device *vdev, unsigned nvqs,
			struct virtqueue *vqs[],
			vq_callback_t *callbacks[],
			const char *names[])
{
	struct kvm_device *kdev = to_kvmdev(vdev);
	int i;

	/* We must have this many virtqueues. */
	if (nvqs > kdev->desc->num_vq)
		return -ENOENT;

	for (i = 0; i < nvqs; ++i) {
		vqs[i] = kvm_find_vq(vdev, i, callbacks[i], names[i]);
		if (IS_ERR(vqs[i]))
			goto error;
	}
	return 0;

error:
	kvm_del_vqs(vdev);
	return PTR_ERR(vqs[i]);
}