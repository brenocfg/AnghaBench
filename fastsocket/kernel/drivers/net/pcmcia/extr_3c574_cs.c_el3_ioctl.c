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
struct net_device {unsigned int base_addr; int /*<<< orphan*/  name; } ;
struct mii_ioctl_data {int phy_id; int reg_num; int /*<<< orphan*/  val_in; int /*<<< orphan*/  val_out; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifrn_name; } ;
struct ifreq {TYPE_1__ ifr_ifrn; } ;
struct el3_private {int phys; int /*<<< orphan*/  window_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EL3WINDOW (int) ; 
 int /*<<< orphan*/  EL3_CMD ; 
 int EOPNOTSUPP ; 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 int inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdio_read (unsigned int,int,int) ; 
 int /*<<< orphan*/  mdio_write (unsigned int,int,int,int /*<<< orphan*/ ) ; 
 struct el3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int el3_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct el3_private *lp = netdev_priv(dev);
	unsigned int ioaddr = dev->base_addr;
	struct mii_ioctl_data *data = if_mii(rq);
	int phy = lp->phys & 0x1f;

	DEBUG(2, "%s: In ioct(%-.6s, %#4.4x) %4.4x %4.4x %4.4x %4.4x.\n",
		  dev->name, rq->ifr_ifrn.ifrn_name, cmd,
		  data->phy_id, data->reg_num, data->val_in, data->val_out);

	switch(cmd) {
	case SIOCGMIIPHY:		/* Get the address of the PHY in use. */
		data->phy_id = phy;
	case SIOCGMIIREG:		/* Read the specified MII register. */
		{
			int saved_window;
			unsigned long flags;

			spin_lock_irqsave(&lp->window_lock, flags);
			saved_window = inw(ioaddr + EL3_CMD) >> 13;
			EL3WINDOW(4);
			data->val_out = mdio_read(ioaddr, data->phy_id & 0x1f,
						  data->reg_num & 0x1f);
			EL3WINDOW(saved_window);
			spin_unlock_irqrestore(&lp->window_lock, flags);
			return 0;
		}
	case SIOCSMIIREG:		/* Write the specified MII register */
		{
			int saved_window;
                       unsigned long flags;

			spin_lock_irqsave(&lp->window_lock, flags);
			saved_window = inw(ioaddr + EL3_CMD) >> 13;
			EL3WINDOW(4);
			mdio_write(ioaddr, data->phy_id & 0x1f,
				   data->reg_num & 0x1f, data->val_in);
			EL3WINDOW(saved_window);
			spin_unlock_irqrestore(&lp->window_lock, flags);
			return 0;
		}
	default:
		return -EOPNOTSUPP;
	}
}