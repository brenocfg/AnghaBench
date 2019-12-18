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
struct vxgedev {int no_of_vpath; int /*<<< orphan*/  vp_lockup_timer; TYPE_1__* vpaths; int /*<<< orphan*/  vp_reset; } ;
struct TYPE_4__ {scalar_t__ prev_rx_frms; scalar_t__ rx_frms; } ;
struct vxge_ring {int last_status; TYPE_2__ stats; int /*<<< orphan*/  handle; } ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;
struct TYPE_3__ {int /*<<< orphan*/  fifo; struct vxge_ring ring; } ;

/* Variables and functions */
 int HZ ; 
 int VXGE_HW_FAIL ; 
 int VXGE_HW_OK ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ *) ; 
 int vxge_hw_vpath_check_leak (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxge_stop_tx_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vxge_vpath_intr_disable (struct vxgedev*,int) ; 

__attribute__((used)) static void vxge_poll_vp_lockup(unsigned long data)
{
	struct vxgedev *vdev = (struct vxgedev *)data;
	int i;
	struct vxge_ring *ring;
	enum vxge_hw_status status = VXGE_HW_OK;

	for (i = 0; i < vdev->no_of_vpath; i++) {
		ring = &vdev->vpaths[i].ring;
		/* Did this vpath received any packets */
		if (ring->stats.prev_rx_frms == ring->stats.rx_frms) {
			status = vxge_hw_vpath_check_leak(ring->handle);

			/* Did it received any packets last time */
			if ((VXGE_HW_FAIL == status) &&
				(VXGE_HW_FAIL == ring->last_status)) {

				/* schedule vpath reset */
				if (!test_and_set_bit(i, &vdev->vp_reset)) {

					/* disable interrupts for this vpath */
					vxge_vpath_intr_disable(vdev, i);

					/* stop the queue for this vpath */
					vxge_stop_tx_queue(&vdev->vpaths[i].
								fifo);
					continue;
				}
			}
		}
		ring->stats.prev_rx_frms = ring->stats.rx_frms;
		ring->last_status = status;
	}

	/* Check every 1 milli second */
	mod_timer(&vdev->vp_lockup_timer, jiffies + HZ / 1000);
}