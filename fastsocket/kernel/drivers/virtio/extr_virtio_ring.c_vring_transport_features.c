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
struct virtio_device {int /*<<< orphan*/  features; } ;

/* Variables and functions */
#define  VIRTIO_RING_F_EVENT_IDX 129 
#define  VIRTIO_RING_F_INDIRECT_DESC 128 
 unsigned int VIRTIO_TRANSPORT_F_END ; 
 unsigned int VIRTIO_TRANSPORT_F_START ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 

void vring_transport_features(struct virtio_device *vdev)
{
	unsigned int i;

	for (i = VIRTIO_TRANSPORT_F_START; i < VIRTIO_TRANSPORT_F_END; i++) {
		switch (i) {
		case VIRTIO_RING_F_INDIRECT_DESC:
			break;
		case VIRTIO_RING_F_EVENT_IDX:
			break;
		default:
			/* We don't understand this bit. */
			clear_bit(i, vdev->features);
		}
	}
}