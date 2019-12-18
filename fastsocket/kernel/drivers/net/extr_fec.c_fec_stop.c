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
struct fec_enet_private {int phy_speed; scalar_t__ hwp; scalar_t__ link; } ;

/* Variables and functions */
 scalar_t__ FEC_ECNTRL ; 
 int FEC_ENET_GRA ; 
 int FEC_ENET_MII ; 
 scalar_t__ FEC_IEVENT ; 
 scalar_t__ FEC_IMASK ; 
 scalar_t__ FEC_MII_SPEED ; 
 scalar_t__ FEC_X_CNTRL ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void
fec_stop(struct net_device *dev)
{
	struct fec_enet_private *fep = netdev_priv(dev);

	/* We cannot expect a graceful transmit stop without link !!! */
	if (fep->link) {
		writel(1, fep->hwp + FEC_X_CNTRL); /* Graceful transmit stop */
		udelay(10);
		if (!(readl(fep->hwp + FEC_IEVENT) & FEC_ENET_GRA))
			printk("fec_stop : Graceful transmit stop did not complete !\n");
	}

	/* Whack a reset.  We should wait for this. */
	writel(1, fep->hwp + FEC_ECNTRL);
	udelay(10);

	/* Clear outstanding MII command interrupts. */
	writel(FEC_ENET_MII, fep->hwp + FEC_IEVENT);

	writel(FEC_ENET_MII, fep->hwp + FEC_IMASK);
	writel(fep->phy_speed, fep->hwp + FEC_MII_SPEED);
}