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
typedef  scalar_t__ u32 ;
struct virtnet_info {struct virtio_device* vdev; } ;
struct virtio_device {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  VIRTIO_NET_F_CSUM ; 
 int ethtool_op_set_tx_hw_csum (struct net_device*,scalar_t__) ; 
 struct virtnet_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  virtio_has_feature (struct virtio_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int virtnet_set_tx_csum(struct net_device *dev, u32 data)
{
	struct virtnet_info *vi = netdev_priv(dev);
	struct virtio_device *vdev = vi->vdev;

	if (data && !virtio_has_feature(vdev, VIRTIO_NET_F_CSUM))
		return -ENOSYS;

	return ethtool_op_set_tx_hw_csum(dev, data);
}