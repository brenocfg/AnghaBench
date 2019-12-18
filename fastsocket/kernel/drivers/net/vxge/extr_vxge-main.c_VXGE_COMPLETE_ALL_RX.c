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
struct vxgedev {int no_of_vpath; TYPE_1__* vpaths; } ;
struct vxge_ring {int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {struct vxge_ring ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  vxge_hw_vpath_poll_rx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void VXGE_COMPLETE_ALL_RX(struct vxgedev *vdev)
{
	int i;
	struct vxge_ring *ring;

	/* Complete all receives*/
	for (i = 0; i < vdev->no_of_vpath; i++) {
		ring = &vdev->vpaths[i].ring;
		vxge_hw_vpath_poll_rx(ring->handle);
	}
}