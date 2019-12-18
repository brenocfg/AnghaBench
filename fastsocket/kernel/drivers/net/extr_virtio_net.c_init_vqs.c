#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vq_callback_t ;
struct virtqueue {int dummy; } ;
struct virtnet_info {TYPE_2__* dev; TYPE_3__* vdev; struct virtqueue* cvq; struct virtqueue* svq; struct virtqueue* rvq; } ;
struct TYPE_7__ {TYPE_1__* config; } ;
struct TYPE_6__ {int /*<<< orphan*/  features; } ;
struct TYPE_5__ {int (* find_vqs ) (TYPE_3__*,int,struct virtqueue**,int /*<<< orphan*/ **,char const**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NETIF_F_HW_VLAN_FILTER ; 
 int /*<<< orphan*/  VIRTIO_NET_F_CTRL_VLAN ; 
 int /*<<< orphan*/  VIRTIO_NET_F_CTRL_VQ ; 
 int /*<<< orphan*/ * skb_recv_done ; 
 int /*<<< orphan*/ * skb_xmit_done ; 
 int stub1 (TYPE_3__*,int,struct virtqueue**,int /*<<< orphan*/ **,char const**) ; 
 scalar_t__ virtio_has_feature (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_vqs(struct virtnet_info *vi)
{
	struct virtqueue *vqs[3];
	vq_callback_t *callbacks[] = { skb_recv_done, skb_xmit_done, NULL};
	const char *names[] = { "input", "output", "control" };
	int nvqs, err;

	/* We expect two virtqueues, receive then send,
	 * and optionally control. */
	nvqs = virtio_has_feature(vi->vdev, VIRTIO_NET_F_CTRL_VQ) ? 3 : 2;

	err = vi->vdev->config->find_vqs(vi->vdev, nvqs, vqs, callbacks, names);
	if (err)
		return err;

	vi->rvq = vqs[0];
	vi->svq = vqs[1];

	if (virtio_has_feature(vi->vdev, VIRTIO_NET_F_CTRL_VQ)) {
		vi->cvq = vqs[2];

		if (virtio_has_feature(vi->vdev, VIRTIO_NET_F_CTRL_VLAN))
			vi->dev->features |= NETIF_F_HW_VLAN_FILTER;
	}
	return 0;
}