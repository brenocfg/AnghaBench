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
struct TYPE_2__ {int type; } ;
struct ixgbe_hw {int device_id; TYPE_1__ phy; } ;
typedef  enum ixgbe_media_type { ____Placeholder_ixgbe_media_type } ixgbe_media_type ;

/* Variables and functions */
#define  IXGBE_DEV_ID_82598 141 
#define  IXGBE_DEV_ID_82598AF_DUAL_PORT 140 
#define  IXGBE_DEV_ID_82598AF_SINGLE_PORT 139 
#define  IXGBE_DEV_ID_82598AT 138 
#define  IXGBE_DEV_ID_82598AT2 137 
#define  IXGBE_DEV_ID_82598EB_CX4 136 
#define  IXGBE_DEV_ID_82598EB_SFP_LOM 135 
#define  IXGBE_DEV_ID_82598EB_XF_LR 134 
#define  IXGBE_DEV_ID_82598_BX 133 
#define  IXGBE_DEV_ID_82598_CX4_DUAL_PORT 132 
#define  IXGBE_DEV_ID_82598_DA_DUAL_PORT 131 
#define  IXGBE_DEV_ID_82598_SR_DUAL_PORT_EM 130 
 int ixgbe_media_type_backplane ; 
 int ixgbe_media_type_copper ; 
 int ixgbe_media_type_cx4 ; 
 int ixgbe_media_type_fiber ; 
 int ixgbe_media_type_unknown ; 
#define  ixgbe_phy_cu_unknown 129 
#define  ixgbe_phy_tn 128 

__attribute__((used)) static enum ixgbe_media_type ixgbe_get_media_type_82598(struct ixgbe_hw *hw)
{
	enum ixgbe_media_type media_type;

	/* Detect if there is a copper PHY attached. */
	switch (hw->phy.type) {
	case ixgbe_phy_cu_unknown:
	case ixgbe_phy_tn:
		media_type = ixgbe_media_type_copper;
		goto out;
	default:
		break;
	}

	/* Media type for I82598 is based on device ID */
	switch (hw->device_id) {
	case IXGBE_DEV_ID_82598:
	case IXGBE_DEV_ID_82598_BX:
		/* Default device ID is mezzanine card KX/KX4 */
		media_type = ixgbe_media_type_backplane;
		break;
	case IXGBE_DEV_ID_82598AF_DUAL_PORT:
	case IXGBE_DEV_ID_82598AF_SINGLE_PORT:
	case IXGBE_DEV_ID_82598_DA_DUAL_PORT:
	case IXGBE_DEV_ID_82598_SR_DUAL_PORT_EM:
	case IXGBE_DEV_ID_82598EB_XF_LR:
	case IXGBE_DEV_ID_82598EB_SFP_LOM:
		media_type = ixgbe_media_type_fiber;
		break;
	case IXGBE_DEV_ID_82598EB_CX4:
	case IXGBE_DEV_ID_82598_CX4_DUAL_PORT:
		media_type = ixgbe_media_type_cx4;
		break;
	case IXGBE_DEV_ID_82598AT:
	case IXGBE_DEV_ID_82598AT2:
		media_type = ixgbe_media_type_copper;
		break;
	default:
		media_type = ixgbe_media_type_unknown;
		break;
	}
out:
	return media_type;
}