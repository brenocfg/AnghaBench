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
typedef  unsigned char uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct et131x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MiRead (struct et131x_adapter*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  PHY_1000_STATUS ; 
 int /*<<< orphan*/  PHY_CONTROL ; 
 int /*<<< orphan*/  PHY_PHY_STATUS ; 
 int /*<<< orphan*/  PHY_STATUS ; 
 int TRUEPHY_ANEG_COMPLETE ; 
 int TRUEPHY_ANEG_DISABLED ; 
 int TRUEPHY_ANEG_NOT_COMPLETE ; 
 int TRUEPHY_CFG_MASTER ; 
 int TRUEPHY_CFG_SLAVE ; 
 int TRUEPHY_POLARITY_INVERTED ; 
 int TRUEPHY_POLARITY_NORMAL ; 

void ET1310_PhyLinkStatus(struct et131x_adapter *etdev,
			  uint8_t *link_status,
			  uint32_t *autoneg,
			  uint32_t *linkspeed,
			  uint32_t *duplex_mode,
			  uint32_t *mdi_mdix,
			  uint32_t *masterslave, uint32_t *polarity)
{
	uint16_t mistatus = 0;
	uint16_t is1000BaseT = 0;
	uint16_t vmi_phystatus = 0;
	uint16_t control = 0;

	MiRead(etdev, PHY_STATUS, &mistatus);
	MiRead(etdev, PHY_1000_STATUS, &is1000BaseT);
	MiRead(etdev, PHY_PHY_STATUS, &vmi_phystatus);
	MiRead(etdev, PHY_CONTROL, &control);

	if (link_status) {
		*link_status =
		    (unsigned char)((vmi_phystatus & 0x0040) ? 1 : 0);
	}

	if (autoneg) {
		*autoneg =
		    (control & 0x1000) ? ((vmi_phystatus & 0x0020) ?
					    TRUEPHY_ANEG_COMPLETE :
					    TRUEPHY_ANEG_NOT_COMPLETE) :
		    TRUEPHY_ANEG_DISABLED;
	}

	if (linkspeed)
		*linkspeed = (vmi_phystatus & 0x0300) >> 8;

	if (duplex_mode)
		*duplex_mode = (vmi_phystatus & 0x0080) >> 7;

	if (mdi_mdix)
		/* NOTE: Need to complete this */
		*mdi_mdix = 0;

	if (masterslave) {
		*masterslave =
		    (is1000BaseT & 0x4000) ? TRUEPHY_CFG_MASTER :
		    TRUEPHY_CFG_SLAVE;
	}

	if (polarity) {
		*polarity =
		    (vmi_phystatus & 0x0400) ? TRUEPHY_POLARITY_INVERTED :
		    TRUEPHY_POLARITY_NORMAL;
	}
}