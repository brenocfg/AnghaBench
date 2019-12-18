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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/ * get_firmware_version; int /*<<< orphan*/ * setup_link; int /*<<< orphan*/ * check_link; int /*<<< orphan*/  (* identify ) (struct ixgbe_hw*) ;int /*<<< orphan*/ * write_i2c_byte; int /*<<< orphan*/ * read_i2c_byte; } ;
struct ixgbe_phy_info {int qsfp_shared_i2c_bus; int type; TYPE_2__ ops; } ;
struct TYPE_3__ {scalar_t__ (* get_media_type ) (struct ixgbe_hw*) ;int /*<<< orphan*/ * get_link_capabilities; int /*<<< orphan*/ * setup_link; } ;
struct ixgbe_mac_info {TYPE_1__ ops; } ;
struct ixgbe_hw {scalar_t__ device_id; struct ixgbe_phy_info phy; struct ixgbe_mac_info mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 scalar_t__ IXGBE_DEV_ID_82599_QSFP_SF_QP ; 
 int /*<<< orphan*/  IXGBE_ESDP ; 
 int /*<<< orphan*/  IXGBE_ESDP_SDP0 ; 
 int /*<<< orphan*/  IXGBE_ESDP_SDP0_DIR ; 
 int /*<<< orphan*/  IXGBE_ESDP_SDP0_NATIVE ; 
 int /*<<< orphan*/  IXGBE_ESDP_SDP1_DIR ; 
 int /*<<< orphan*/  IXGBE_ESDP_SDP1_NATIVE ; 
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_check_phy_link_tnx ; 
 int /*<<< orphan*/  ixgbe_get_copper_link_capabilities_generic ; 
 int /*<<< orphan*/  ixgbe_get_phy_firmware_version_tnx ; 
 int /*<<< orphan*/  ixgbe_init_mac_link_ops_82599 (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_media_type_copper ; 
#define  ixgbe_phy_tn 128 
 int /*<<< orphan*/  ixgbe_read_i2c_byte_82599 ; 
 int /*<<< orphan*/  ixgbe_setup_copper_link_82599 ; 
 int /*<<< orphan*/  ixgbe_setup_phy_link_tnx ; 
 int /*<<< orphan*/  ixgbe_write_i2c_byte_82599 ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*) ; 

__attribute__((used)) static s32 ixgbe_init_phy_ops_82599(struct ixgbe_hw *hw)
{
	struct ixgbe_mac_info *mac = &hw->mac;
	struct ixgbe_phy_info *phy = &hw->phy;
	s32 ret_val = 0;
	u32 esdp;

	if (hw->device_id == IXGBE_DEV_ID_82599_QSFP_SF_QP) {
		/* Store flag indicating I2C bus access control unit. */
		hw->phy.qsfp_shared_i2c_bus = true;

		/* Initialize access to QSFP+ I2C bus */
		esdp = IXGBE_READ_REG(hw, IXGBE_ESDP);
		esdp |= IXGBE_ESDP_SDP0_DIR;
		esdp &= ~IXGBE_ESDP_SDP1_DIR;
		esdp &= ~IXGBE_ESDP_SDP0;
		esdp &= ~IXGBE_ESDP_SDP0_NATIVE;
		esdp &= ~IXGBE_ESDP_SDP1_NATIVE;
		IXGBE_WRITE_REG(hw, IXGBE_ESDP, esdp);
		IXGBE_WRITE_FLUSH(hw);

		phy->ops.read_i2c_byte = &ixgbe_read_i2c_byte_82599;
		phy->ops.write_i2c_byte = &ixgbe_write_i2c_byte_82599;
	}

	/* Identify the PHY or SFP module */
	ret_val = phy->ops.identify(hw);

	/* Setup function pointers based on detected SFP module and speeds */
	ixgbe_init_mac_link_ops_82599(hw);

	/* If copper media, overwrite with copper function pointers */
	if (mac->ops.get_media_type(hw) == ixgbe_media_type_copper) {
		mac->ops.setup_link = &ixgbe_setup_copper_link_82599;
		mac->ops.get_link_capabilities =
			&ixgbe_get_copper_link_capabilities_generic;
	}

	/* Set necessary function pointers based on phy type */
	switch (hw->phy.type) {
	case ixgbe_phy_tn:
		phy->ops.check_link = &ixgbe_check_phy_link_tnx;
		phy->ops.setup_link = &ixgbe_setup_phy_link_tnx;
		phy->ops.get_firmware_version =
		             &ixgbe_get_phy_firmware_version_tnx;
		break;
	default:
		break;
	}

	return ret_val;
}