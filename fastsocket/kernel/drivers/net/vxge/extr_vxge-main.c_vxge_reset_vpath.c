#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vxgedev {TYPE_2__* vpaths; int /*<<< orphan*/  vp_reset; int /*<<< orphan*/  state; } ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;
struct TYPE_4__ {scalar_t__ last_status; } ;
struct TYPE_5__ {int /*<<< orphan*/  fifo; TYPE_1__ ring; scalar_t__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  VXGE_ERR ; 
 int VXGE_HW_FAIL ; 
 scalar_t__ VXGE_HW_OK ; 
 int /*<<< orphan*/  __VXGE_STATE_RESET_CARD ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 scalar_t__ is_vxge_card_up (struct vxgedev*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vxge_debug_init (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vxge_hw_vpath_bcast_enable (scalar_t__) ; 
 int /*<<< orphan*/  vxge_hw_vpath_enable (scalar_t__) ; 
 scalar_t__ vxge_hw_vpath_recover_from_reset (scalar_t__) ; 
 scalar_t__ vxge_hw_vpath_reset (scalar_t__) ; 
 int /*<<< orphan*/  vxge_hw_vpath_rx_doorbell_init (scalar_t__) ; 
 int /*<<< orphan*/  vxge_restore_vpath_mac_addr (TYPE_2__*) ; 
 int /*<<< orphan*/  vxge_restore_vpath_vid_table (TYPE_2__*) ; 
 int /*<<< orphan*/  vxge_vpath_intr_enable (struct vxgedev*,int) ; 
 int /*<<< orphan*/  vxge_wake_tx_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vxge_reset_vpath(struct vxgedev *vdev, int vp_id)
{
	enum vxge_hw_status status = VXGE_HW_OK;
	int ret = 0;

	/* check if device is down already */
	if (unlikely(!is_vxge_card_up(vdev)))
		return 0;

	/* is device reset already scheduled */
	if (test_bit(__VXGE_STATE_RESET_CARD, &vdev->state))
		return 0;

	if (vdev->vpaths[vp_id].handle) {
		if (vxge_hw_vpath_reset(vdev->vpaths[vp_id].handle)
				== VXGE_HW_OK) {
			if (is_vxge_card_up(vdev) &&
				vxge_hw_vpath_recover_from_reset(
					vdev->vpaths[vp_id].handle)
					!= VXGE_HW_OK) {
				vxge_debug_init(VXGE_ERR,
					"vxge_hw_vpath_recover_from_reset"
					"failed for vpath:%d", vp_id);
				return status;
			}
		} else {
			vxge_debug_init(VXGE_ERR,
				"vxge_hw_vpath_reset failed for"
				"vpath:%d", vp_id);
				return status;
		}
	} else
		return VXGE_HW_FAIL;

	vxge_restore_vpath_mac_addr(&vdev->vpaths[vp_id]);
	vxge_restore_vpath_vid_table(&vdev->vpaths[vp_id]);

	/* Enable all broadcast */
	vxge_hw_vpath_bcast_enable(vdev->vpaths[vp_id].handle);

	/* Enable the interrupts */
	vxge_vpath_intr_enable(vdev, vp_id);

	smp_wmb();

	/* Enable the flow of traffic through the vpath */
	vxge_hw_vpath_enable(vdev->vpaths[vp_id].handle);

	smp_wmb();
	vxge_hw_vpath_rx_doorbell_init(vdev->vpaths[vp_id].handle);
	vdev->vpaths[vp_id].ring.last_status = VXGE_HW_OK;

	/* Vpath reset done */
	clear_bit(vp_id, &vdev->vp_reset);

	/* Start the vpath queue */
	vxge_wake_tx_queue(&vdev->vpaths[vp_id].fifo, NULL);

	return ret;
}