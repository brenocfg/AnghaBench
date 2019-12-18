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
typedef  int /*<<< orphan*/  u64 ;
struct __vxge_hw_vpath_handle {int dummy; } ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;

/* Variables and functions */
 int VXGE_HW_ERR_INVALID_HANDLE ; 
 int VXGE_HW_OK ; 
 int /*<<< orphan*/  VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION_ADD_ENTRY ; 
 int /*<<< orphan*/  VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_VID ; 
 int /*<<< orphan*/  VXGE_HW_RTS_ACCESS_STEER_DATA0_VLAN_ID (int /*<<< orphan*/ ) ; 
 int __vxge_hw_vpath_rts_table_set (struct __vxge_hw_vpath_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum vxge_hw_status
vxge_hw_vpath_vid_add(struct __vxge_hw_vpath_handle *vp, u64 vid)
{
	enum vxge_hw_status status = VXGE_HW_OK;

	if (vp == NULL) {
		status = VXGE_HW_ERR_INVALID_HANDLE;
		goto exit;
	}

	status = __vxge_hw_vpath_rts_table_set(vp,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION_ADD_ENTRY,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_VID,
			0, VXGE_HW_RTS_ACCESS_STEER_DATA0_VLAN_ID(vid), 0);
exit:
	return status;
}