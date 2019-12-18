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
struct mii_ioctl_data {int reg_num; int /*<<< orphan*/  val_in; int /*<<< orphan*/  val_out; int /*<<< orphan*/  phy_id; } ;
struct ifreq {int dummy; } ;
struct cas {int /*<<< orphan*/  pm_mutex; int /*<<< orphan*/  lock; int /*<<< orphan*/  phy_addr; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 int /*<<< orphan*/  cas_mif_poll (struct cas*,int) ; 
 int /*<<< orphan*/  cas_phy_read (struct cas*,int) ; 
 int cas_phy_write (struct cas*,int,int /*<<< orphan*/ ) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cas* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cas_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct cas *cp = netdev_priv(dev);
	struct mii_ioctl_data *data = if_mii(ifr);
	unsigned long flags;
	int rc = -EOPNOTSUPP;

	/* Hold the PM mutex while doing ioctl's or we may collide
	 * with open/close and power management and oops.
	 */
	mutex_lock(&cp->pm_mutex);
	switch (cmd) {
	case SIOCGMIIPHY:		/* Get address of MII PHY in use. */
		data->phy_id = cp->phy_addr;
		/* Fallthrough... */

	case SIOCGMIIREG:		/* Read MII PHY register. */
		spin_lock_irqsave(&cp->lock, flags);
		cas_mif_poll(cp, 0);
		data->val_out = cas_phy_read(cp, data->reg_num & 0x1f);
		cas_mif_poll(cp, 1);
		spin_unlock_irqrestore(&cp->lock, flags);
		rc = 0;
		break;

	case SIOCSMIIREG:		/* Write MII PHY register. */
		spin_lock_irqsave(&cp->lock, flags);
		cas_mif_poll(cp, 0);
		rc = cas_phy_write(cp, data->reg_num & 0x1f, data->val_in);
		cas_mif_poll(cp, 1);
		spin_unlock_irqrestore(&cp->lock, flags);
		break;
	default:
		break;
	};

	mutex_unlock(&cp->pm_mutex);
	return rc;
}