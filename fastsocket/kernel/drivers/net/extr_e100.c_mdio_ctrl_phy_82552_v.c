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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  phy_id; } ;
struct nic {TYPE_1__ mii; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int ADVERTISE_100FULL ; 
 int ADVERTISE_100HALF ; 
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED100 ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 scalar_t__ MII_BMCR ; 
 scalar_t__ mdi_write ; 
 int mdio_ctrl_hw (struct nic*,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int mdio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 mdio_ctrl_phy_82552_v(struct nic *nic,
				 u32 addr,
				 u32 dir,
				 u32 reg,
				 u16 data)
{
	if ((reg == MII_BMCR) && (dir == mdi_write)) {
		if (data & (BMCR_ANRESTART | BMCR_ANENABLE)) {
			u16 advert = mdio_read(nic->netdev, nic->mii.phy_id,
							MII_ADVERTISE);

			/*
			 * Workaround Si issue where sometimes the part will not
			 * autoneg to 100Mbps even when advertised.
			 */
			if (advert & ADVERTISE_100FULL)
				data |= BMCR_SPEED100 | BMCR_FULLDPLX;
			else if (advert & ADVERTISE_100HALF)
				data |= BMCR_SPEED100;
		}
	}
	return mdio_ctrl_hw(nic, addr, dir, reg, data);
}