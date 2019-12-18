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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int req_line_speed; scalar_t__ req_duplex; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  MDIO_WC_DEVAD ; 
 int /*<<< orphan*/  MDIO_WC_REG_COMBO_IEEE0_MIICTRL ; 
 int /*<<< orphan*/  MDIO_WC_REG_RX66_CONTROL ; 
 int /*<<< orphan*/  MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X1 ; 
 int /*<<< orphan*/  MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X2 ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int SPEED_AUTO_NEG ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bnx2x_cl45_read_and_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_cl45_read_or_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_warpcore_set_lpi_passthrough (struct bnx2x_phy*,struct link_params*) ; 

__attribute__((used)) static void bnx2x_warpcore_set_sgmii_speed(struct bnx2x_phy *phy,
					   struct link_params *params,
					   u8 fiber_mode,
					   u8 always_autoneg)
{
	struct bnx2x *bp = params->bp;
	u16 val16, digctrl_kx1, digctrl_kx2;

	/* Clear XFI clock comp in non-10G single lane mode. */
	bnx2x_cl45_read_and_write(bp, phy, MDIO_WC_DEVAD,
				  MDIO_WC_REG_RX66_CONTROL, ~(3<<13));

	bnx2x_warpcore_set_lpi_passthrough(phy, params);

	if (always_autoneg || phy->req_line_speed == SPEED_AUTO_NEG) {
		/* SGMII Autoneg */
		bnx2x_cl45_read_or_write(bp, phy, MDIO_WC_DEVAD,
					 MDIO_WC_REG_COMBO_IEEE0_MIICTRL,
					 0x1000);
		DP(NETIF_MSG_LINK, "set SGMII AUTONEG\n");
	} else {
		bnx2x_cl45_read(bp, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_COMBO_IEEE0_MIICTRL, &val16);
		val16 &= 0xcebf;
		switch (phy->req_line_speed) {
		case SPEED_10:
			break;
		case SPEED_100:
			val16 |= 0x2000;
			break;
		case SPEED_1000:
			val16 |= 0x0040;
			break;
		default:
			DP(NETIF_MSG_LINK,
			   "Speed not supported: 0x%x\n", phy->req_line_speed);
			return;
		}

		if (phy->req_duplex == DUPLEX_FULL)
			val16 |= 0x0100;

		bnx2x_cl45_write(bp, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_COMBO_IEEE0_MIICTRL, val16);

		DP(NETIF_MSG_LINK, "set SGMII force speed %d\n",
			       phy->req_line_speed);
		bnx2x_cl45_read(bp, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_COMBO_IEEE0_MIICTRL, &val16);
		DP(NETIF_MSG_LINK, "  (readback) %x\n", val16);
	}

	/* SGMII Slave mode and disable signal detect */
	bnx2x_cl45_read(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X1, &digctrl_kx1);
	if (fiber_mode)
		digctrl_kx1 = 1;
	else
		digctrl_kx1 &= 0xff4a;

	bnx2x_cl45_write(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X1,
			digctrl_kx1);

	/* Turn off parallel detect */
	bnx2x_cl45_read(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X2, &digctrl_kx2);
	bnx2x_cl45_write(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X2,
			(digctrl_kx2 & ~(1<<2)));

	/* Re-enable parallel detect */
	bnx2x_cl45_write(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X2,
			(digctrl_kx2 | (1<<2)));

	/* Enable autodet */
	bnx2x_cl45_write(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X1,
			(digctrl_kx1 | 0x10));
}