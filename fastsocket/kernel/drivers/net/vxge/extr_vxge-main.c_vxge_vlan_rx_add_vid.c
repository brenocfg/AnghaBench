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
struct vxgedev {int no_of_vpath; struct vxge_vpath* vpaths; } ;
struct vxge_vpath {int /*<<< orphan*/  handle; int /*<<< orphan*/  is_open; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  vxge_hw_vpath_vid_add (int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void
vxge_vlan_rx_add_vid(struct net_device *dev, unsigned short vid)
{
	struct vxgedev *vdev;
	struct vxge_vpath *vpath;
	int vp_id;

	vdev = (struct vxgedev *)netdev_priv(dev);

	/* Add these vlan to the vid table */
	for (vp_id = 0; vp_id < vdev->no_of_vpath; vp_id++) {
		vpath = &vdev->vpaths[vp_id];
		if (!vpath->is_open)
			continue;
		vxge_hw_vpath_vid_add(vpath->handle, vid);
	}
}