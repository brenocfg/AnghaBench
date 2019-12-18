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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  func; } ;
struct ixgbe_hw {TYPE_1__ bus; } ;
struct ixgbe_adapter {int eeprom_cap; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int IXGBE_DEVICE_CAPS_WOL_MASK ; 
 int IXGBE_DEVICE_CAPS_WOL_PORT0 ; 
 int IXGBE_DEVICE_CAPS_WOL_PORT0_1 ; 
#define  IXGBE_DEV_ID_82599EN_SFP 140 
#define  IXGBE_DEV_ID_82599_COMBO_BACKPLANE 139 
#define  IXGBE_DEV_ID_82599_KX4 138 
#define  IXGBE_DEV_ID_82599_SFP 137 
#define  IXGBE_DEV_ID_X540T 136 
#define  IXGBE_DEV_ID_X540T1 135 
#define  IXGBE_SUBDEV_ID_82599EN_SFP_OCP1 134 
#define  IXGBE_SUBDEV_ID_82599_560FLR 133 
#define  IXGBE_SUBDEV_ID_82599_ECNA_DP 132 
 int IXGBE_SUBDEV_ID_82599_KX4_KR_MEZZ ; 
#define  IXGBE_SUBDEV_ID_82599_LOM_SFP 131 
#define  IXGBE_SUBDEV_ID_82599_RNDC 130 
#define  IXGBE_SUBDEV_ID_82599_SFP 129 
#define  IXGBE_SUBDEV_ID_82599_SP_560FLR 128 

int ixgbe_wol_supported(struct ixgbe_adapter *adapter, u16 device_id,
			u16 subdevice_id)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u16 wol_cap = adapter->eeprom_cap & IXGBE_DEVICE_CAPS_WOL_MASK;
	int is_wol_supported = 0;

	switch (device_id) {
	case IXGBE_DEV_ID_82599_SFP:
		/* Only these subdevices could supports WOL */
		switch (subdevice_id) {
		case IXGBE_SUBDEV_ID_82599_560FLR:
			/* only support first port */
			if (hw->bus.func != 0)
				break;
		case IXGBE_SUBDEV_ID_82599_SP_560FLR:
		case IXGBE_SUBDEV_ID_82599_SFP:
		case IXGBE_SUBDEV_ID_82599_RNDC:
		case IXGBE_SUBDEV_ID_82599_ECNA_DP:
		case IXGBE_SUBDEV_ID_82599_LOM_SFP:
			is_wol_supported = 1;
			break;
		}
		break;
	case IXGBE_DEV_ID_82599EN_SFP:
		/* Only this subdevice supports WOL */
		switch (subdevice_id) {
		case IXGBE_SUBDEV_ID_82599EN_SFP_OCP1:
			is_wol_supported = 1;
			break;
		}
		break;
	case IXGBE_DEV_ID_82599_COMBO_BACKPLANE:
		/* All except this subdevice support WOL */
		if (subdevice_id != IXGBE_SUBDEV_ID_82599_KX4_KR_MEZZ)
			is_wol_supported = 1;
		break;
	case IXGBE_DEV_ID_82599_KX4:
		is_wol_supported = 1;
		break;
	case IXGBE_DEV_ID_X540T:
	case IXGBE_DEV_ID_X540T1:
		/* check eeprom to see if enabled wol */
		if ((wol_cap == IXGBE_DEVICE_CAPS_WOL_PORT0_1) ||
		    ((wol_cap == IXGBE_DEVICE_CAPS_WOL_PORT0) &&
		     (hw->bus.func == 0))) {
			is_wol_supported = 1;
		}
		break;
	}

	return is_wol_supported;
}