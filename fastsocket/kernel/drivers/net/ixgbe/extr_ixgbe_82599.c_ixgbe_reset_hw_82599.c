#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {scalar_t__ (* stop_adapter ) (struct ixgbe_hw*) ;scalar_t__ (* setup_sfp ) (struct ixgbe_hw*) ;scalar_t__ (* acquire_swfw_sync ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* get_wwn_prefix ) (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_rar ) (struct ixgbe_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* get_san_mac_addr ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* init_rx_addrs ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* get_mac_addr ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* release_swfw_sync ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* check_link ) (struct ixgbe_hw*,int /*<<< orphan*/ *,int*,int) ;} ;
struct TYPE_8__ {int cached_autoc; int flags; int orig_link_settings_stored; int orig_autoc; int orig_autoc2; int num_rar_entries; int san_mac_rar_index; int /*<<< orphan*/  wwpn_prefix; int /*<<< orphan*/  wwnn_prefix; TYPE_3__ ops; int /*<<< orphan*/  san_addr; int /*<<< orphan*/  perm_addr; } ;
struct TYPE_5__ {scalar_t__ (* init ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* reset ) (struct ixgbe_hw*) ;} ;
struct TYPE_6__ {int sfp_setup_needed; int reset_disable; scalar_t__ multispeed_fiber; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_4__ mac; scalar_t__ wol_enabled; scalar_t__ mng_fw_enabled; TYPE_2__ phy; int /*<<< orphan*/  force_full_reset; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  ixgbe_link_speed ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_AUTOC ; 
 int /*<<< orphan*/  IXGBE_AUTOC2 ; 
 int IXGBE_AUTOC2_LINK_DISABLE_MASK ; 
 int IXGBE_AUTOC2_UPPER_MASK ; 
 int IXGBE_AUTOC_LMS_MASK ; 
 int /*<<< orphan*/  IXGBE_CTRL ; 
 int IXGBE_CTRL_LNK_RST ; 
 int IXGBE_CTRL_RST ; 
 int IXGBE_CTRL_RST_MASK ; 
 scalar_t__ IXGBE_ERR_RESET_FAILED ; 
 scalar_t__ IXGBE_ERR_SFP_NOT_SUPPORTED ; 
 int IXGBE_FLAGS_DOUBLE_RESET_REQUIRED ; 
 int /*<<< orphan*/  IXGBE_GSSR_MAC_CSR_SM ; 
 int /*<<< orphan*/  IXGBE_RAH_AV ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_clear_tx_pending (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_reset_pipeline_82599 (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_verify_lesm_fw_enabled_82599 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub10 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (struct ixgbe_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct ixgbe_hw*) ; 
 scalar_t__ stub3 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub4 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub5 (struct ixgbe_hw*,int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ stub6 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static s32 ixgbe_reset_hw_82599(struct ixgbe_hw *hw)
{
	ixgbe_link_speed link_speed;
	s32 status;
	u32 ctrl, i, autoc2;
	u32 curr_lms;
	bool link_up = false;

	/* Call adapter stop to disable tx/rx and clear interrupts */
	status = hw->mac.ops.stop_adapter(hw);
	if (status != 0)
		goto reset_hw_out;

	/* flush pending Tx transactions */
	ixgbe_clear_tx_pending(hw);

	/* PHY ops must be identified and initialized prior to reset */

	/* Identify PHY and related function pointers */
	status = hw->phy.ops.init(hw);

	if (status == IXGBE_ERR_SFP_NOT_SUPPORTED)
		goto reset_hw_out;

	/* Setup SFP module if there is one present. */
	if (hw->phy.sfp_setup_needed) {
		status = hw->mac.ops.setup_sfp(hw);
		hw->phy.sfp_setup_needed = false;
	}

	if (status == IXGBE_ERR_SFP_NOT_SUPPORTED)
		goto reset_hw_out;

	/* Reset PHY */
	if (hw->phy.reset_disable == false && hw->phy.ops.reset != NULL)
		hw->phy.ops.reset(hw);

	/* remember AUTOC from before we reset */
	if (hw->mac.cached_autoc)
		curr_lms = hw->mac.cached_autoc & IXGBE_AUTOC_LMS_MASK;
	else
		curr_lms = IXGBE_READ_REG(hw, IXGBE_AUTOC) &
			   IXGBE_AUTOC_LMS_MASK;

mac_reset_top:
	/*
	 * Issue global reset to the MAC. Needs to be SW reset if link is up.
	 * If link reset is used when link is up, it might reset the PHY when
	 * mng is using it.  If link is down or the flag to force full link
	 * reset is set, then perform link reset.
	 */
	ctrl = IXGBE_CTRL_LNK_RST;
	if (!hw->force_full_reset) {
		hw->mac.ops.check_link(hw, &link_speed, &link_up, false);
		if (link_up)
			ctrl = IXGBE_CTRL_RST;
	}

	ctrl |= IXGBE_READ_REG(hw, IXGBE_CTRL);
	IXGBE_WRITE_REG(hw, IXGBE_CTRL, ctrl);
	IXGBE_WRITE_FLUSH(hw);

	/* Poll for reset bit to self-clear indicating reset is complete */
	for (i = 0; i < 10; i++) {
		udelay(1);
		ctrl = IXGBE_READ_REG(hw, IXGBE_CTRL);
		if (!(ctrl & IXGBE_CTRL_RST_MASK))
			break;
	}

	if (ctrl & IXGBE_CTRL_RST_MASK) {
		status = IXGBE_ERR_RESET_FAILED;
		hw_dbg(hw, "Reset polling failed to complete.\n");
	}

	msleep(50);

	/*
	 * Double resets are required for recovery from certain error
	 * conditions.  Between resets, it is necessary to stall to allow time
	 * for any pending HW events to complete.
	 */
	if (hw->mac.flags & IXGBE_FLAGS_DOUBLE_RESET_REQUIRED) {
		hw->mac.flags &= ~IXGBE_FLAGS_DOUBLE_RESET_REQUIRED;
		goto mac_reset_top;
	}

	/*
	 * Store the original AUTOC/AUTOC2 values if they have not been
	 * stored off yet.  Otherwise restore the stored original
	 * values since the reset operation sets back to defaults.
	 */
	hw->mac.cached_autoc = IXGBE_READ_REG(hw, IXGBE_AUTOC);
	autoc2 = IXGBE_READ_REG(hw, IXGBE_AUTOC2);

	/* Enable link if disabled in NVM */
	if (autoc2 & IXGBE_AUTOC2_LINK_DISABLE_MASK) {
		autoc2 &= ~IXGBE_AUTOC2_LINK_DISABLE_MASK;
		IXGBE_WRITE_REG(hw, IXGBE_AUTOC2, autoc2);
		IXGBE_WRITE_FLUSH(hw);
	}

	if (hw->mac.orig_link_settings_stored == false) {
		hw->mac.orig_autoc = hw->mac.cached_autoc;
		hw->mac.orig_autoc2 = autoc2;
		hw->mac.orig_link_settings_stored = true;
	} else {

		/* If MNG FW is running on a multi-speed device that
		 * doesn't autoneg with out driver support we need to
		 * leave LMS in the state it was before we MAC reset.
		 * Likewise if we support WoL we don't want change the
		 * LMS state either.
		 */
		if ((hw->phy.multispeed_fiber && hw->mng_fw_enabled) ||
		    hw->wol_enabled)
			hw->mac.orig_autoc =
				(hw->mac.orig_autoc & ~IXGBE_AUTOC_LMS_MASK) |
				curr_lms;

		if (hw->mac.cached_autoc != hw->mac.orig_autoc) {
			/* Need SW/FW semaphore around AUTOC writes if LESM is
			 * on, likewise reset_pipeline requires us to hold
			 * this lock as it also writes to AUTOC.
			 */
			bool got_lock = false;
			if (ixgbe_verify_lesm_fw_enabled_82599(hw)) {
				status = hw->mac.ops.acquire_swfw_sync(hw,
							IXGBE_GSSR_MAC_CSR_SM);
				if (status)
					goto reset_hw_out;

				got_lock = true;
			}

			IXGBE_WRITE_REG(hw, IXGBE_AUTOC, hw->mac.orig_autoc);
			hw->mac.cached_autoc = hw->mac.orig_autoc;
			ixgbe_reset_pipeline_82599(hw);

			if (got_lock)
				hw->mac.ops.release_swfw_sync(hw,
							IXGBE_GSSR_MAC_CSR_SM);
		}

		if ((autoc2 & IXGBE_AUTOC2_UPPER_MASK) !=
		    (hw->mac.orig_autoc2 & IXGBE_AUTOC2_UPPER_MASK)) {
			autoc2 &= ~IXGBE_AUTOC2_UPPER_MASK;
			autoc2 |= (hw->mac.orig_autoc2 &
			           IXGBE_AUTOC2_UPPER_MASK);
			IXGBE_WRITE_REG(hw, IXGBE_AUTOC2, autoc2);
		}
	}

	/* Store the permanent mac address */
	hw->mac.ops.get_mac_addr(hw, hw->mac.perm_addr);

	/*
	 * Store MAC address from RAR0, clear receive address registers, and
	 * clear the multicast table.  Also reset num_rar_entries to 128,
	 * since we modify this value when programming the SAN MAC address.
	 */
	hw->mac.num_rar_entries = 128;
	hw->mac.ops.init_rx_addrs(hw);

	/* Store the permanent SAN mac address */
	hw->mac.ops.get_san_mac_addr(hw, hw->mac.san_addr);

	/* Add the SAN MAC address to the RAR only if it's a valid address */
	if (is_valid_ether_addr(hw->mac.san_addr)) {
		hw->mac.ops.set_rar(hw, hw->mac.num_rar_entries - 1,
		                    hw->mac.san_addr, 0, IXGBE_RAH_AV);

		/* Save the SAN MAC RAR index */
		hw->mac.san_mac_rar_index = hw->mac.num_rar_entries - 1;

		/* Reserve the last RAR for the SAN MAC address */
		hw->mac.num_rar_entries--;
	}

	/* Store the alternative WWNN/WWPN prefix */
	hw->mac.ops.get_wwn_prefix(hw, &hw->mac.wwnn_prefix,
	                               &hw->mac.wwpn_prefix);

reset_hw_out:
	return status;
}