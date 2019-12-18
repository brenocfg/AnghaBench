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
typedef  int uint ;
struct net_device {int dummy; } ;
struct fec_enet_private {int phy_addr; int phy_id; scalar_t__ phy_speed; scalar_t__ hwp; } ;

/* Variables and functions */
 scalar_t__ FEC_MII_SPEED ; 
 int /*<<< orphan*/  MII_REG_PHYIR1 ; 
 int /*<<< orphan*/  MII_REG_PHYIR2 ; 
 int /*<<< orphan*/  fec_disable_phy_intr (struct net_device*) ; 
 void mii_discover_phy3 (int,struct net_device*) ; 
 int /*<<< orphan*/  mii_queue_unlocked (struct net_device*,int /*<<< orphan*/ ,void (*) (int,struct net_device*)) ; 
 int /*<<< orphan*/  mk_mii_read (int /*<<< orphan*/ ) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
mii_discover_phy(uint mii_reg, struct net_device *dev)
{
	struct fec_enet_private *fep;
	uint phytype;

	fep = netdev_priv(dev);

	if (fep->phy_addr < 32) {
		if ((phytype = (mii_reg & 0xffff)) != 0xffff && phytype != 0) {

			/* Got first part of ID, now get remainder */
			fep->phy_id = phytype << 16;
			mii_queue_unlocked(dev, mk_mii_read(MII_REG_PHYIR2),
							mii_discover_phy3);
		} else {
			fep->phy_addr++;
			mii_queue_unlocked(dev, mk_mii_read(MII_REG_PHYIR1),
							mii_discover_phy);
		}
	} else {
		printk("FEC: No PHY device found.\n");
		/* Disable external MII interface */
		writel(0, fep->hwp + FEC_MII_SPEED);
		fep->phy_speed = 0;
#ifdef HAVE_mii_link_interrupt
		fec_disable_phy_intr(dev);
#endif
	}
}