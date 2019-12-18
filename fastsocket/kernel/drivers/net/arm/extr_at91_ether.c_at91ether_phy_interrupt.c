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
struct net_device {int dummy; } ;
struct at91_private {scalar_t__ phy_type; int /*<<< orphan*/  phy_address; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ MII_BCM5221_ID ; 
 int /*<<< orphan*/  MII_BCMINTR_REG ; 
 scalar_t__ MII_DM9161A_ID ; 
 scalar_t__ MII_DM9161_ID ; 
 scalar_t__ MII_DP83848_ID ; 
 int /*<<< orphan*/  MII_DPPHYSTS_REG ; 
 int /*<<< orphan*/  MII_DSINTR_REG ; 
 int /*<<< orphan*/  MII_ISINTS_REG ; 
 scalar_t__ MII_KS8721_ID ; 
 scalar_t__ MII_LXT971A_ID ; 
 int /*<<< orphan*/  MII_T78Q21INT_REG ; 
 scalar_t__ MII_T78Q21x3_ID ; 
 int /*<<< orphan*/  MII_TPISTATUS ; 
 int /*<<< orphan*/  disable_mdi () ; 
 int /*<<< orphan*/  enable_mdi () ; 
 struct at91_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  read_phy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  update_linkspeed (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t at91ether_phy_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *) dev_id;
	struct at91_private *lp = netdev_priv(dev);
	unsigned int phy;

	/*
	 * This hander is triggered on both edges, but the PHY chips expect
	 * level-triggering.  We therefore have to check if the PHY actually has
	 * an IRQ pending.
	 */
	enable_mdi();
	if ((lp->phy_type == MII_DM9161_ID) || (lp->phy_type == MII_DM9161A_ID)) {
		read_phy(lp->phy_address, MII_DSINTR_REG, &phy);	/* ack interrupt in Davicom PHY */
		if (!(phy & (1 << 0)))
			goto done;
	}
	else if (lp->phy_type == MII_LXT971A_ID) {
		read_phy(lp->phy_address, MII_ISINTS_REG, &phy);	/* ack interrupt in Intel PHY */
		if (!(phy & (1 << 2)))
			goto done;
	}
	else if (lp->phy_type == MII_BCM5221_ID) {
		read_phy(lp->phy_address, MII_BCMINTR_REG, &phy);	/* ack interrupt in Broadcom PHY */
		if (!(phy & (1 << 0)))
			goto done;
	}
	else if (lp->phy_type == MII_KS8721_ID) {
		read_phy(lp->phy_address, MII_TPISTATUS, &phy);		/* ack interrupt in Micrel PHY */
		if (!(phy & ((1 << 2) | 1)))
			goto done;
	}
	else if (lp->phy_type == MII_T78Q21x3_ID) {			/* ack interrupt in Teridian PHY */
		read_phy(lp->phy_address, MII_T78Q21INT_REG, &phy);
		if (!(phy & ((1 << 2) | 1)))
			goto done;
	}
	else if (lp->phy_type == MII_DP83848_ID) {
		read_phy(lp->phy_address, MII_DPPHYSTS_REG, &phy);	/* ack interrupt in DP83848 PHY */
		if (!(phy & (1 << 7)))
			goto done;
	}

	update_linkspeed(dev, 0);

done:
	disable_mdi();

	return IRQ_HANDLED;
}