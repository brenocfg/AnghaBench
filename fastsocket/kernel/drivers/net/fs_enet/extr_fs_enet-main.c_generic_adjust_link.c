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
struct phy_device {int duplex; scalar_t__ speed; scalar_t__ link; } ;
struct net_device {int dummy; } ;
struct fs_enet_private {int oldduplex; scalar_t__ oldspeed; int oldlink; TYPE_1__* ops; struct phy_device* phydev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* restart ) (struct net_device*) ;} ;

/* Variables and functions */
 struct fs_enet_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_link (struct fs_enet_private*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

__attribute__((used)) static void generic_adjust_link(struct  net_device *dev)
{
	struct fs_enet_private *fep = netdev_priv(dev);
	struct phy_device *phydev = fep->phydev;
	int new_state = 0;

	if (phydev->link) {
		/* adjust to duplex mode */
		if (phydev->duplex != fep->oldduplex) {
			new_state = 1;
			fep->oldduplex = phydev->duplex;
		}

		if (phydev->speed != fep->oldspeed) {
			new_state = 1;
			fep->oldspeed = phydev->speed;
		}

		if (!fep->oldlink) {
			new_state = 1;
			fep->oldlink = 1;
		}

		if (new_state)
			fep->ops->restart(dev);
	} else if (fep->oldlink) {
		new_state = 1;
		fep->oldlink = 0;
		fep->oldspeed = 0;
		fep->oldduplex = -1;
	}

	if (new_state && netif_msg_link(fep))
		phy_print_status(phydev);
}