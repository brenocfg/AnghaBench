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
struct ixgb_hw {int device_id; scalar_t__ subsystem_vendor_id; } ;
typedef  int /*<<< orphan*/  ixgb_xpak_vendor ;
typedef  int /*<<< orphan*/  ixgb_phy_type ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
#define  IXGB_DEVICE_ID_82597EX 131 
#define  IXGB_DEVICE_ID_82597EX_CX4 130 
#define  IXGB_DEVICE_ID_82597EX_LR 129 
#define  IXGB_DEVICE_ID_82597EX_SR 128 
 scalar_t__ SUN_SUBVENDOR_ID ; 
 int /*<<< orphan*/  ixgb_identify_xpak_vendor (struct ixgb_hw*) ; 
 int /*<<< orphan*/  ixgb_phy_type_bcm ; 
 int /*<<< orphan*/  ixgb_phy_type_g6005 ; 
 int /*<<< orphan*/  ixgb_phy_type_g6104 ; 
 int /*<<< orphan*/  ixgb_phy_type_txn17201 ; 
 int /*<<< orphan*/  ixgb_phy_type_txn17401 ; 
 int /*<<< orphan*/  ixgb_phy_type_unknown ; 
 int /*<<< orphan*/  ixgb_xpak_vendor_intel ; 

__attribute__((used)) static ixgb_phy_type
ixgb_identify_phy(struct ixgb_hw *hw)
{
	ixgb_phy_type phy_type;
	ixgb_xpak_vendor xpak_vendor;

	DEBUGFUNC("ixgb_identify_phy");

	/* Infer the transceiver/phy type from the device id */
	switch (hw->device_id) {
	case IXGB_DEVICE_ID_82597EX:
		DEBUGOUT("Identified TXN17401 optics\n");
		phy_type = ixgb_phy_type_txn17401;
		break;

	case IXGB_DEVICE_ID_82597EX_SR:
		/* The SR adapters carry two different types of XPAK optics
		 * modules; read the vendor identifier to determine the exact
		 * type of optics. */
		xpak_vendor = ixgb_identify_xpak_vendor(hw);
		if (xpak_vendor == ixgb_xpak_vendor_intel) {
			DEBUGOUT("Identified TXN17201 optics\n");
			phy_type = ixgb_phy_type_txn17201;
		} else {
			DEBUGOUT("Identified G6005 optics\n");
			phy_type = ixgb_phy_type_g6005;
		}
		break;
	case IXGB_DEVICE_ID_82597EX_LR:
		DEBUGOUT("Identified G6104 optics\n");
		phy_type = ixgb_phy_type_g6104;
		break;
	case IXGB_DEVICE_ID_82597EX_CX4:
		DEBUGOUT("Identified CX4\n");
		xpak_vendor = ixgb_identify_xpak_vendor(hw);
		if (xpak_vendor == ixgb_xpak_vendor_intel) {
			DEBUGOUT("Identified TXN17201 optics\n");
			phy_type = ixgb_phy_type_txn17201;
		} else {
			DEBUGOUT("Identified G6005 optics\n");
			phy_type = ixgb_phy_type_g6005;
		}
		break;
	default:
		DEBUGOUT("Unknown physical layer module\n");
		phy_type = ixgb_phy_type_unknown;
		break;
	}

	/* update phy type for sun specific board */
	if (hw->subsystem_vendor_id == SUN_SUBVENDOR_ID)
		phy_type = ixgb_phy_type_bcm;

	return (phy_type);
}