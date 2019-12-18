#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  vpaths_open; } ;
struct vxgedev {int no_of_vpath; TYPE_2__* vpaths; TYPE_1__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/ * handle; scalar_t__ is_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  vxge_hw_vpath_close (int /*<<< orphan*/ *) ; 

void vxge_close_vpaths(struct vxgedev *vdev, int index)
{
	int i;
	for (i = index; i < vdev->no_of_vpath; i++) {
		if (vdev->vpaths[i].handle && vdev->vpaths[i].is_open) {
			vxge_hw_vpath_close(vdev->vpaths[i].handle);
			vdev->stats.vpaths_open--;
		}
		vdev->vpaths[i].is_open = 0;
		vdev->vpaths[i].handle  = NULL;
	}
}