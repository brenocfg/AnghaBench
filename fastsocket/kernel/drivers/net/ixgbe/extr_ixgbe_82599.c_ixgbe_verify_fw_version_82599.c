#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_5__ {int /*<<< orphan*/  (* read ) (struct ixgbe_hw*,scalar_t__,int*) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {scalar_t__ media_type; } ;
struct ixgbe_hw {TYPE_3__ eeprom; TYPE_1__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ IXGBE_ERR_EEPROM_VERSION ; 
 scalar_t__ IXGBE_FW_PASSTHROUGH_PATCH_CONFIG_PTR ; 
 scalar_t__ IXGBE_FW_PATCH_VERSION_4 ; 
 scalar_t__ IXGBE_FW_PTR ; 
 scalar_t__ ixgbe_media_type_fiber ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,scalar_t__,int*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,scalar_t__,int*) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*,scalar_t__,int*) ; 

__attribute__((used)) static s32 ixgbe_verify_fw_version_82599(struct ixgbe_hw *hw)
{
	s32 status = IXGBE_ERR_EEPROM_VERSION;
	u16 fw_offset, fw_ptp_cfg_offset;
	u16 fw_version = 0;

	/* firmware check is only necessary for SFI devices */
	if (hw->phy.media_type != ixgbe_media_type_fiber) {
		status = 0;
		goto fw_version_out;
	}

	/* get the offset to the Firmware Module block */
	hw->eeprom.ops.read(hw, IXGBE_FW_PTR, &fw_offset);

	if ((fw_offset == 0) || (fw_offset == 0xFFFF))
		goto fw_version_out;

	/* get the offset to the Pass Through Patch Configuration block */
	hw->eeprom.ops.read(hw, (fw_offset +
	                         IXGBE_FW_PASSTHROUGH_PATCH_CONFIG_PTR),
	                         &fw_ptp_cfg_offset);

	if ((fw_ptp_cfg_offset == 0) || (fw_ptp_cfg_offset == 0xFFFF))
		goto fw_version_out;

	/* get the firmware version */
	hw->eeprom.ops.read(hw, (fw_ptp_cfg_offset +
	                         IXGBE_FW_PATCH_VERSION_4),
	                         &fw_version);

	if (fw_version > 0x5)
		status = 0;

fw_version_out:
	return status;
}