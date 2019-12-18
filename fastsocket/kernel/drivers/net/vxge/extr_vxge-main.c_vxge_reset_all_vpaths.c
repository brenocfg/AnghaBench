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
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;
struct TYPE_2__ {scalar_t__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  VXGE_ERR ; 
 scalar_t__ VXGE_HW_OK ; 
 scalar_t__ is_vxge_card_up (struct vxgedev*) ; 
 int /*<<< orphan*/  vxge_debug_init (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ vxge_hw_vpath_recover_from_reset (scalar_t__) ; 
 scalar_t__ vxge_hw_vpath_reset (scalar_t__) ; 

enum vxge_hw_status vxge_reset_all_vpaths(struct vxgedev *vdev)
{
	int i;
	enum vxge_hw_status status = VXGE_HW_OK;

	for (i = 0; i < vdev->no_of_vpath; i++)
		if (vdev->vpaths[i].handle) {
			if (vxge_hw_vpath_reset(vdev->vpaths[i].handle)
					== VXGE_HW_OK) {
				if (is_vxge_card_up(vdev) &&
					vxge_hw_vpath_recover_from_reset(
						vdev->vpaths[i].handle)
						!= VXGE_HW_OK) {
					vxge_debug_init(VXGE_ERR,
						"vxge_hw_vpath_recover_"
						"from_reset failed for vpath: "
						"%d", i);
					return status;
				}
			} else {
				vxge_debug_init(VXGE_ERR,
					"vxge_hw_vpath_reset failed for "
					"vpath:%d", i);
					return status;
			}
		}
	return status;
}