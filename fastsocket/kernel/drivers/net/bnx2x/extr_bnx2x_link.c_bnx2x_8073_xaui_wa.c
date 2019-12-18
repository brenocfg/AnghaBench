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
typedef  int u16 ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_REG_8073_CHIP_REV ; 
 int /*<<< orphan*/  MDIO_PMA_REG_8073_SPEED_LINK_STATUS ; 
 int /*<<< orphan*/  MDIO_PMA_REG_8073_XAUI_WA ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int bnx2x_8073_xaui_wa(struct bnx2x *bp, struct bnx2x_phy *phy)
{
	u16 val, cnt, cnt1 ;

	bnx2x_cl45_read(bp, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_8073_CHIP_REV, &val);

	if (val > 0) {
		/* No need to workaround in 8073 A1 */
		return 0;
	}
	/* XAUI workaround in 8073 A0: */

	/* After loading the boot ROM and restarting Autoneg, poll
	 * Dev1, Reg $C820:
	 */

	for (cnt = 0; cnt < 1000; cnt++) {
		bnx2x_cl45_read(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_8073_SPEED_LINK_STATUS,
				&val);
		  /* If bit [14] = 0 or bit [13] = 0, continue on with
		   * system initialization (XAUI work-around not required, as
		   * these bits indicate 2.5G or 1G link up).
		   */
		if (!(val & (1<<14)) || !(val & (1<<13))) {
			DP(NETIF_MSG_LINK, "XAUI work-around not required\n");
			return 0;
		} else if (!(val & (1<<15))) {
			DP(NETIF_MSG_LINK, "bit 15 went off\n");
			/* If bit 15 is 0, then poll Dev1, Reg $C841 until it's
			 * MSB (bit15) goes to 1 (indicating that the XAUI
			 * workaround has completed), then continue on with
			 * system initialization.
			 */
			for (cnt1 = 0; cnt1 < 1000; cnt1++) {
				bnx2x_cl45_read(bp, phy,
					MDIO_PMA_DEVAD,
					MDIO_PMA_REG_8073_XAUI_WA, &val);
				if (val & (1<<15)) {
					DP(NETIF_MSG_LINK,
					  "XAUI workaround has completed\n");
					return 0;
				 }
				 usleep_range(3000, 6000);
			}
			break;
		}
		usleep_range(3000, 6000);
	}
	DP(NETIF_MSG_LINK, "Warning: XAUI work-around timeout !!!\n");
	return -EINVAL;
}