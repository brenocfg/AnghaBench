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
struct TYPE_5__ {int /*<<< orphan*/  (* check_link ) (struct ixgbe_hw*,int /*<<< orphan*/ *,int*,int) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {int media_type; } ;
struct ixgbe_hw {int /*<<< orphan*/  device_id; TYPE_3__ mac; TYPE_1__ phy; } ;
typedef  int /*<<< orphan*/  ixgbe_link_speed ;

/* Variables and functions */
#define  IXGBE_DEV_ID_82599_T3_LOM 134 
#define  IXGBE_DEV_ID_X540T 133 
#define  IXGBE_DEV_ID_X540T1 132 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_1GB_FULL ; 
#define  ixgbe_media_type_backplane 131 
#define  ixgbe_media_type_copper 130 
#define  ixgbe_media_type_fiber 129 
#define  ixgbe_media_type_fiber_fixed 128 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int /*<<< orphan*/ *,int*,int) ; 

bool ixgbe_device_supports_autoneg_fc(struct ixgbe_hw *hw)
{
	bool supported = false;
	ixgbe_link_speed speed;
	bool link_up;

	switch (hw->phy.media_type) {
	case ixgbe_media_type_fiber_fixed:
	case ixgbe_media_type_fiber:
		hw->mac.ops.check_link(hw, &speed, &link_up, false);
		/* if link is down, assume supported */
		if (link_up)
			supported = speed == IXGBE_LINK_SPEED_1GB_FULL ?
				true : false;
		else
			supported = true;
		break;
	case ixgbe_media_type_backplane:
		supported = true;
		break;
	case ixgbe_media_type_copper:
		/* only some copper devices support flow control autoneg */
		switch (hw->device_id) {
		case IXGBE_DEV_ID_82599_T3_LOM:
		case IXGBE_DEV_ID_X540T:
		case IXGBE_DEV_ID_X540T1:
			supported = true;
			break;
		default:
			break;
		}
	default:
		break;
	}

	return supported;
}