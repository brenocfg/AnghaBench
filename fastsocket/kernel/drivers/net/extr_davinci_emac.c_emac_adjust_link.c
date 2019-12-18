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
struct phy_device {scalar_t__ speed; int /*<<< orphan*/  duplex; scalar_t__ link; } ;
struct net_device {int dummy; } ;
struct emac_priv {scalar_t__ speed; int link; int /*<<< orphan*/  lock; struct phy_device* phydev; int /*<<< orphan*/  duplex; } ;

/* Variables and functions */
 int /*<<< orphan*/  emac_update_phystatus (struct emac_priv*) ; 
 struct emac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void emac_adjust_link(struct net_device *ndev)
{
	struct emac_priv *priv = netdev_priv(ndev);
	struct phy_device *phydev = priv->phydev;
	unsigned long flags;
	int new_state = 0;

	spin_lock_irqsave(&priv->lock, flags);

	if (phydev->link) {
		/* check the mode of operation - full/half duplex */
		if (phydev->duplex != priv->duplex) {
			new_state = 1;
			priv->duplex = phydev->duplex;
		}
		if (phydev->speed != priv->speed) {
			new_state = 1;
			priv->speed = phydev->speed;
		}
		if (!priv->link) {
			new_state = 1;
			priv->link = 1;
		}

	} else if (priv->link) {
		new_state = 1;
		priv->link = 0;
		priv->speed = 0;
		priv->duplex = ~0;
	}
	if (new_state) {
		emac_update_phystatus(priv);
		phy_print_status(priv->phydev);
	}

	spin_unlock_irqrestore(&priv->lock, flags);
}