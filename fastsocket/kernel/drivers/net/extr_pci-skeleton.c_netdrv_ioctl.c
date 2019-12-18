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
struct netdrv_private {int* phys; int /*<<< orphan*/  lock; } ;
struct net_device {int dummy; } ;
struct mii_ioctl_data {int phy_id; int reg_num; int /*<<< orphan*/  val_in; int /*<<< orphan*/  val_out; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int EOPNOTSUPP ; 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 int /*<<< orphan*/  mdio_read (struct net_device*,int,int) ; 
 int /*<<< orphan*/  mdio_write (struct net_device*,int,int,int /*<<< orphan*/ ) ; 
 struct netdrv_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int netdrv_ioctl (struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct netdrv_private *tp = netdev_priv(dev);
	struct mii_ioctl_data *data = if_mii(rq);
	unsigned long flags;
	int rc = 0;

	DPRINTK ("ENTER\n");

	switch (cmd) {
	case SIOCGMIIPHY:		/* Get address of MII PHY in use. */
		data->phy_id = tp->phys[0] & 0x3f;
		/* Fall Through */

	case SIOCGMIIREG:		/* Read MII PHY register. */
		spin_lock_irqsave (&tp->lock, flags);
		data->val_out = mdio_read (dev, data->phy_id & 0x1f, data->reg_num & 0x1f);
		spin_unlock_irqrestore (&tp->lock, flags);
		break;

	case SIOCSMIIREG:		/* Write MII PHY register. */
		spin_lock_irqsave (&tp->lock, flags);
		mdio_write (dev, data->phy_id & 0x1f, data->reg_num & 0x1f, data->val_in);
		spin_unlock_irqrestore (&tp->lock, flags);
		break;

	default:
		rc = -EOPNOTSUPP;
		break;
	}

	DPRINTK ("EXIT, returning %d\n", rc);
	return rc;
}