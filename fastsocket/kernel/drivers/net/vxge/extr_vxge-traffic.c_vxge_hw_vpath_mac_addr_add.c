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
typedef  int u8 ;
typedef  int u64 ;
typedef  size_t u32 ;
struct __vxge_hw_vpath_handle {int dummy; } ;
typedef  enum vxge_hw_vpath_mac_addr_add_mode { ____Placeholder_vxge_hw_vpath_mac_addr_add_mode } vxge_hw_vpath_mac_addr_add_mode ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;

/* Variables and functions */
 size_t ETH_ALEN ; 
 int VXGE_HW_ERR_INVALID_HANDLE ; 
 int VXGE_HW_OK ; 
 int /*<<< orphan*/  VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION_ADD_ENTRY ; 
 int /*<<< orphan*/  VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_DA ; 
 int /*<<< orphan*/  VXGE_HW_RTS_ACCESS_STEER_DATA0_DA_MAC_ADDR (int) ; 
 int VXGE_HW_RTS_ACCESS_STEER_DATA1_DA_MAC_ADDR_MASK (int) ; 
 int VXGE_HW_RTS_ACCESS_STEER_DATA1_DA_MAC_ADDR_MODE (size_t) ; 
#define  VXGE_HW_VPATH_MAC_ADDR_ADD_DUPLICATE 130 
#define  VXGE_HW_VPATH_MAC_ADDR_DISCARD_DUPLICATE 129 
#define  VXGE_HW_VPATH_MAC_ADDR_REPLACE_DUPLICATE 128 
 int __vxge_hw_vpath_rts_table_set (struct __vxge_hw_vpath_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

enum vxge_hw_status
vxge_hw_vpath_mac_addr_add(
	struct __vxge_hw_vpath_handle *vp,
	u8 (macaddr)[ETH_ALEN],
	u8 (macaddr_mask)[ETH_ALEN],
	enum vxge_hw_vpath_mac_addr_add_mode duplicate_mode)
{
	u32 i;
	u64 data1 = 0ULL;
	u64 data2 = 0ULL;
	enum vxge_hw_status status = VXGE_HW_OK;

	if (vp == NULL) {
		status = VXGE_HW_ERR_INVALID_HANDLE;
		goto exit;
	}

	for (i = 0; i < ETH_ALEN; i++) {
		data1 <<= 8;
		data1 |= (u8)macaddr[i];

		data2 <<= 8;
		data2 |= (u8)macaddr_mask[i];
	}

	switch (duplicate_mode) {
	case VXGE_HW_VPATH_MAC_ADDR_ADD_DUPLICATE:
		i = 0;
		break;
	case VXGE_HW_VPATH_MAC_ADDR_DISCARD_DUPLICATE:
		i = 1;
		break;
	case VXGE_HW_VPATH_MAC_ADDR_REPLACE_DUPLICATE:
		i = 2;
		break;
	default:
		i = 0;
		break;
	}

	status = __vxge_hw_vpath_rts_table_set(vp,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION_ADD_ENTRY,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_DA,
			0,
			VXGE_HW_RTS_ACCESS_STEER_DATA0_DA_MAC_ADDR(data1),
			VXGE_HW_RTS_ACCESS_STEER_DATA1_DA_MAC_ADDR_MASK(data2)|
			VXGE_HW_RTS_ACCESS_STEER_DATA1_DA_MAC_ADDR_MODE(i));
exit:
	return status;
}