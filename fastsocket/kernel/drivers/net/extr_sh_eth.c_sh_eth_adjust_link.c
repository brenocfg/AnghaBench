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
struct sh_eth_private {int duplex; scalar_t__ speed; scalar_t__ link; TYPE_1__* cd; struct phy_device* phydev; } ;
struct phy_device {scalar_t__ link; int duplex; scalar_t__ speed; } ;
struct net_device {scalar_t__ base_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_rate ) (struct net_device*) ;int /*<<< orphan*/  (* set_duplex ) (struct net_device*) ;} ;

/* Variables and functions */
 scalar_t__ ECMR ; 
 int ECMR_DM ; 
 int ECMR_TXF ; 
 scalar_t__ PHY_DOWN ; 
 int ctrl_inl (scalar_t__) ; 
 int /*<<< orphan*/  ctrl_outl (int,scalar_t__) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int /*<<< orphan*/  stub2 (struct net_device*) ; 

__attribute__((used)) static void sh_eth_adjust_link(struct net_device *ndev)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	struct phy_device *phydev = mdp->phydev;
	u32 ioaddr = ndev->base_addr;
	int new_state = 0;

	if (phydev->link != PHY_DOWN) {
		if (phydev->duplex != mdp->duplex) {
			new_state = 1;
			mdp->duplex = phydev->duplex;
			if (mdp->cd->set_duplex)
				mdp->cd->set_duplex(ndev);
		}

		if (phydev->speed != mdp->speed) {
			new_state = 1;
			mdp->speed = phydev->speed;
			if (mdp->cd->set_rate)
				mdp->cd->set_rate(ndev);
		}
		if (mdp->link == PHY_DOWN) {
			ctrl_outl((ctrl_inl(ioaddr + ECMR) & ~ECMR_TXF)
					| ECMR_DM, ioaddr + ECMR);
			new_state = 1;
			mdp->link = phydev->link;
		}
	} else if (mdp->link) {
		new_state = 1;
		mdp->link = PHY_DOWN;
		mdp->speed = 0;
		mdp->duplex = -1;
	}

	if (new_state)
		phy_print_status(phydev);
}