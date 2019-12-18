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
struct TYPE_4__ {scalar_t__ (* get_media_type ) (struct ixgbe_hw*) ;int /*<<< orphan*/ * setup_link; int /*<<< orphan*/ * flap_tx_laser; int /*<<< orphan*/ * enable_tx_laser; int /*<<< orphan*/ * disable_tx_laser; } ;
struct ixgbe_mac_info {TYPE_2__ ops; } ;
struct TYPE_3__ {scalar_t__ smart_speed; scalar_t__ multispeed_fiber; } ;
struct ixgbe_hw {TYPE_1__ phy; int /*<<< orphan*/  mng_fw_enabled; struct ixgbe_mac_info mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbe_disable_tx_laser_multispeed_fiber ; 
 int /*<<< orphan*/  ixgbe_enable_tx_laser_multispeed_fiber ; 
 int /*<<< orphan*/  ixgbe_flap_tx_laser_multispeed_fiber ; 
 scalar_t__ ixgbe_media_type_backplane ; 
 scalar_t__ ixgbe_media_type_fiber ; 
 int /*<<< orphan*/  ixgbe_setup_mac_link_82599 ; 
 int /*<<< orphan*/  ixgbe_setup_mac_link_multispeed_fiber ; 
 int /*<<< orphan*/  ixgbe_setup_mac_link_smartspeed ; 
 scalar_t__ ixgbe_smart_speed_auto ; 
 scalar_t__ ixgbe_smart_speed_on ; 
 int /*<<< orphan*/  ixgbe_verify_lesm_fw_enabled_82599 (struct ixgbe_hw*) ; 
 scalar_t__ stub1 (struct ixgbe_hw*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*) ; 

__attribute__((used)) static void ixgbe_init_mac_link_ops_82599(struct ixgbe_hw *hw)
{
	struct ixgbe_mac_info *mac = &hw->mac;

	/* enable the laser control functions for SFP+ fiber
	 * and MNG not enabled
	 */
	if ((mac->ops.get_media_type(hw) == ixgbe_media_type_fiber) &&
	    !hw->mng_fw_enabled) {
		mac->ops.disable_tx_laser =
		                       &ixgbe_disable_tx_laser_multispeed_fiber;
		mac->ops.enable_tx_laser =
		                        &ixgbe_enable_tx_laser_multispeed_fiber;
		mac->ops.flap_tx_laser = &ixgbe_flap_tx_laser_multispeed_fiber;
	} else {
		mac->ops.disable_tx_laser = NULL;
		mac->ops.enable_tx_laser = NULL;
		mac->ops.flap_tx_laser = NULL;
	}

	if (hw->phy.multispeed_fiber) {
		/* Set up dual speed SFP+ support */
		mac->ops.setup_link = &ixgbe_setup_mac_link_multispeed_fiber;
	} else {
		if ((mac->ops.get_media_type(hw) ==
		     ixgbe_media_type_backplane) &&
		    (hw->phy.smart_speed == ixgbe_smart_speed_auto ||
		     hw->phy.smart_speed == ixgbe_smart_speed_on) &&
		     !ixgbe_verify_lesm_fw_enabled_82599(hw))
			mac->ops.setup_link = &ixgbe_setup_mac_link_smartspeed;
		else
			mac->ops.setup_link = &ixgbe_setup_mac_link_82599;
	}
}