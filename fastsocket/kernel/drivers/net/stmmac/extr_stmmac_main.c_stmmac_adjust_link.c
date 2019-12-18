#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct stmmac_priv {unsigned int flow_ctrl; unsigned int pause; int oldduplex; int speed; int oldlink; int /*<<< orphan*/  lock; int /*<<< orphan*/  bsp_priv; int /*<<< orphan*/  (* fix_mac_speed ) (int /*<<< orphan*/ ,int) ;TYPE_4__* mac_type; int /*<<< orphan*/  is_gmac; struct phy_device* phydev; } ;
struct phy_device {int duplex; int speed; scalar_t__ pause; scalar_t__ link; int /*<<< orphan*/  addr; } ;
struct net_device {unsigned long base_addr; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  port; int /*<<< orphan*/  speed; int /*<<< orphan*/  duplex; } ;
struct TYPE_7__ {TYPE_2__ link; } ;
struct TYPE_8__ {TYPE_3__ hw; TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* flow_ctrl ) (unsigned long,int,unsigned int,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DEBUG ; 
 scalar_t__ MAC_CTRL_REG ; 
 int SPEED_100 ; 
 int /*<<< orphan*/  likely (int /*<<< orphan*/ ) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_link (struct stmmac_priv*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (unsigned long,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void stmmac_adjust_link(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	struct phy_device *phydev = priv->phydev;
	unsigned long ioaddr = dev->base_addr;
	unsigned long flags;
	int new_state = 0;
	unsigned int fc = priv->flow_ctrl, pause_time = priv->pause;

	if (phydev == NULL)
		return;

	DBG(probe, DEBUG, "stmmac_adjust_link: called.  address %d link %d\n",
	    phydev->addr, phydev->link);

	spin_lock_irqsave(&priv->lock, flags);
	if (phydev->link) {
		u32 ctrl = readl(ioaddr + MAC_CTRL_REG);

		/* Now we make sure that we can be in full duplex mode.
		 * If not, we operate in half-duplex mode. */
		if (phydev->duplex != priv->oldduplex) {
			new_state = 1;
			if (!(phydev->duplex))
				ctrl &= ~priv->mac_type->hw.link.duplex;
			else
				ctrl |= priv->mac_type->hw.link.duplex;
			priv->oldduplex = phydev->duplex;
		}
		/* Flow Control operation */
		if (phydev->pause)
			priv->mac_type->ops->flow_ctrl(ioaddr, phydev->duplex,
						       fc, pause_time);

		if (phydev->speed != priv->speed) {
			new_state = 1;
			switch (phydev->speed) {
			case 1000:
				if (likely(priv->is_gmac))
					ctrl &= ~priv->mac_type->hw.link.port;
				break;
			case 100:
			case 10:
				if (priv->is_gmac) {
					ctrl |= priv->mac_type->hw.link.port;
					if (phydev->speed == SPEED_100) {
						ctrl |=
						    priv->mac_type->hw.link.
						    speed;
					} else {
						ctrl &=
						    ~(priv->mac_type->hw.
						      link.speed);
					}
				} else {
					ctrl &= ~priv->mac_type->hw.link.port;
				}
				priv->fix_mac_speed(priv->bsp_priv,
						    phydev->speed);
				break;
			default:
				if (netif_msg_link(priv))
					pr_warning("%s: Speed (%d) is not 10"
				       " or 100!\n", dev->name, phydev->speed);
				break;
			}

			priv->speed = phydev->speed;
		}

		writel(ctrl, ioaddr + MAC_CTRL_REG);

		if (!priv->oldlink) {
			new_state = 1;
			priv->oldlink = 1;
		}
	} else if (priv->oldlink) {
		new_state = 1;
		priv->oldlink = 0;
		priv->speed = 0;
		priv->oldduplex = -1;
	}

	if (new_state && netif_msg_link(priv))
		phy_print_status(phydev);

	spin_unlock_irqrestore(&priv->lock, flags);

	DBG(probe, DEBUG, "stmmac_adjust_link: exiting\n");
}