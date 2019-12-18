#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_9__ {scalar_t__ (* acquire_swfw_sync ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* release_swfw_sync ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {TYPE_4__ ops; } ;
struct TYPE_6__ {scalar_t__ func; } ;
struct ixgbe_hw {TYPE_5__ mac; TYPE_1__ bus; } ;
struct TYPE_7__ {scalar_t__ ret_status; int /*<<< orphan*/  cmd_resv; } ;
struct TYPE_8__ {TYPE_2__ cmd_or_resp; scalar_t__ buf_len; scalar_t__ checksum; int /*<<< orphan*/  cmd; } ;
struct ixgbe_hic_drv_info {TYPE_3__ hdr; scalar_t__ pad2; scalar_t__ pad; void* ver_sub; void* ver_build; void* ver_min; void* ver_maj; void* port_num; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  fw_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  FW_CEM_CMD_DRIVER_INFO ; 
 scalar_t__ FW_CEM_CMD_DRIVER_INFO_LEN ; 
 int /*<<< orphan*/  FW_CEM_CMD_RESERVED ; 
 scalar_t__ FW_CEM_HDR_LEN ; 
 int FW_CEM_MAX_RETRIES ; 
 scalar_t__ FW_CEM_RESP_STATUS_SUCCESS ; 
 scalar_t__ IXGBE_ERR_HOST_INTERFACE_COMMAND ; 
 scalar_t__ IXGBE_ERR_SWFW_SYNC ; 
 int /*<<< orphan*/  IXGBE_GSSR_SW_MNG_SM ; 
 scalar_t__ ixgbe_calculate_checksum (void**,scalar_t__) ; 
 scalar_t__ ixgbe_host_interface_command (struct ixgbe_hw*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 

s32 ixgbe_set_fw_drv_ver_generic(struct ixgbe_hw *hw, u8 maj, u8 min,
				 u8 build, u8 sub)
{
	struct ixgbe_hic_drv_info fw_cmd;
	int i;
	s32 ret_val = 0;

	if (hw->mac.ops.acquire_swfw_sync(hw, IXGBE_GSSR_SW_MNG_SM) != 0) {
		ret_val = IXGBE_ERR_SWFW_SYNC;
		goto out;
	}

	fw_cmd.hdr.cmd = FW_CEM_CMD_DRIVER_INFO;
	fw_cmd.hdr.buf_len = FW_CEM_CMD_DRIVER_INFO_LEN;
	fw_cmd.hdr.cmd_or_resp.cmd_resv = FW_CEM_CMD_RESERVED;
	fw_cmd.port_num = (u8)hw->bus.func;
	fw_cmd.ver_maj = maj;
	fw_cmd.ver_min = min;
	fw_cmd.ver_build = build;
	fw_cmd.ver_sub = sub;
	fw_cmd.hdr.checksum = 0;
	fw_cmd.hdr.checksum = ixgbe_calculate_checksum((u8 *)&fw_cmd,
				(FW_CEM_HDR_LEN + fw_cmd.hdr.buf_len));
	fw_cmd.pad = 0;
	fw_cmd.pad2 = 0;

	for (i = 0; i <= FW_CEM_MAX_RETRIES; i++) {
		ret_val = ixgbe_host_interface_command(hw, (u32 *)&fw_cmd,
						       sizeof(fw_cmd));
		if (ret_val != 0)
			continue;

		if (fw_cmd.hdr.cmd_or_resp.ret_status ==
		    FW_CEM_RESP_STATUS_SUCCESS)
			ret_val = 0;
		else
			ret_val = IXGBE_ERR_HOST_INTERFACE_COMMAND;

		break;
	}

	hw->mac.ops.release_swfw_sync(hw, IXGBE_GSSR_SW_MNG_SM);
out:
	return ret_val;
}