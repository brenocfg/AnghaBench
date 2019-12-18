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
typedef  int /*<<< orphan*/  u32 ;
struct smsc9420_pdata {scalar_t__ last_duplex; int last_carrier; struct phy_device* phy_dev; } ;
struct phy_device {scalar_t__ duplex; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINK ; 
 int /*<<< orphan*/  MAC_CR ; 
 int /*<<< orphan*/  MAC_CR_FDPX_ ; 
 struct smsc9420_pdata* netdev_priv (struct net_device*) ; 
 int netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  smsc9420_phy_update_flowcontrol (struct smsc9420_pdata*) ; 
 int /*<<< orphan*/  smsc9420_reg_read (struct smsc9420_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc9420_reg_write (struct smsc9420_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void smsc9420_phy_adjust_link(struct net_device *dev)
{
	struct smsc9420_pdata *pd = netdev_priv(dev);
	struct phy_device *phy_dev = pd->phy_dev;
	int carrier;

	if (phy_dev->duplex != pd->last_duplex) {
		u32 mac_cr = smsc9420_reg_read(pd, MAC_CR);
		if (phy_dev->duplex) {
			smsc_dbg(LINK, "full duplex mode");
			mac_cr |= MAC_CR_FDPX_;
		} else {
			smsc_dbg(LINK, "half duplex mode");
			mac_cr &= ~MAC_CR_FDPX_;
		}
		smsc9420_reg_write(pd, MAC_CR, mac_cr);

		smsc9420_phy_update_flowcontrol(pd);
		pd->last_duplex = phy_dev->duplex;
	}

	carrier = netif_carrier_ok(dev);
	if (carrier != pd->last_carrier) {
		if (carrier)
			smsc_dbg(LINK, "carrier OK");
		else
			smsc_dbg(LINK, "no carrier");
		pd->last_carrier = carrier;
	}
}