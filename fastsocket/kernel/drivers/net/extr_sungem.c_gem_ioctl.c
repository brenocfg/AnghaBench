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
struct mii_ioctl_data {int phy_id; int reg_num; int /*<<< orphan*/  val_in; int /*<<< orphan*/  val_out; } ;
struct ifreq {int dummy; } ;
struct gem {int mii_phy_addr; int /*<<< orphan*/  pm_mutex; int /*<<< orphan*/  lock; int /*<<< orphan*/  running; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EOPNOTSUPP ; 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 int /*<<< orphan*/  __phy_read (struct gem*,int,int) ; 
 int /*<<< orphan*/  __phy_write (struct gem*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gem_get_cell (struct gem*) ; 
 int /*<<< orphan*/  gem_put_cell (struct gem*) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct gem* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int gem_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct gem *gp = netdev_priv(dev);
	struct mii_ioctl_data *data = if_mii(ifr);
	int rc = -EOPNOTSUPP;
	unsigned long flags;

	/* Hold the PM mutex while doing ioctl's or we may collide
	 * with power management.
	 */
	mutex_lock(&gp->pm_mutex);

	spin_lock_irqsave(&gp->lock, flags);
	gem_get_cell(gp);
	spin_unlock_irqrestore(&gp->lock, flags);

	switch (cmd) {
	case SIOCGMIIPHY:		/* Get address of MII PHY in use. */
		data->phy_id = gp->mii_phy_addr;
		/* Fallthrough... */

	case SIOCGMIIREG:		/* Read MII PHY register. */
		if (!gp->running)
			rc = -EAGAIN;
		else {
			data->val_out = __phy_read(gp, data->phy_id & 0x1f,
						   data->reg_num & 0x1f);
			rc = 0;
		}
		break;

	case SIOCSMIIREG:		/* Write MII PHY register. */
		if (!gp->running)
			rc = -EAGAIN;
		else {
			__phy_write(gp, data->phy_id & 0x1f, data->reg_num & 0x1f,
				    data->val_in);
			rc = 0;
		}
		break;
	};

	spin_lock_irqsave(&gp->lock, flags);
	gem_put_cell(gp);
	spin_unlock_irqrestore(&gp->lock, flags);

	mutex_unlock(&gp->pm_mutex);

	return rc;
}