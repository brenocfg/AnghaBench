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
struct net_device {int base_addr; int flags; } ;
struct arcnet_local {int setup; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUGMSG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  D_NORMAL ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
 int PROMISCset ; 
 int /*<<< orphan*/  SET_SUBADR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUB_SETUP1 ; 
 int /*<<< orphan*/  _XREG ; 
 struct arcnet_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void com20020_set_mc_list(struct net_device *dev)
{
	struct arcnet_local *lp = netdev_priv(dev);
	int ioaddr = dev->base_addr;

	if ((dev->flags & IFF_PROMISC) && (dev->flags & IFF_UP)) {	/* Enable promiscuous mode */
		if (!(lp->setup & PROMISCset))
			BUGMSG(D_NORMAL, "Setting promiscuous flag...\n");
		SET_SUBADR(SUB_SETUP1);
		lp->setup |= PROMISCset;
		outb(lp->setup, _XREG);
	} else
		/* Disable promiscuous mode, use normal mode */
	{
		if ((lp->setup & PROMISCset))
			BUGMSG(D_NORMAL, "Resetting promiscuous flag...\n");
		SET_SUBADR(SUB_SETUP1);
		lp->setup &= ~PROMISCset;
		outb(lp->setup, _XREG);
	}
}