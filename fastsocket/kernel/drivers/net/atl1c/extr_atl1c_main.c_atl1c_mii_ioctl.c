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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct mii_ioctl_data {int reg_num; int /*<<< orphan*/  val_in; int /*<<< orphan*/  val_out; int /*<<< orphan*/  phy_id; } ;
struct ifreq {int dummy; } ;
struct atl1c_adapter {int /*<<< orphan*/  mdio_lock; int /*<<< orphan*/  hw; struct pci_dev* pdev; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int EIO ; 
 int EOPNOTSUPP ; 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 int /*<<< orphan*/  atl1c_read_phy_reg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atl1c_write_phy_reg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 struct atl1c_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int atl1c_mii_ioctl(struct net_device *netdev,
			   struct ifreq *ifr, int cmd)
{
	struct atl1c_adapter *adapter = netdev_priv(netdev);
	struct pci_dev *pdev = adapter->pdev;
	struct mii_ioctl_data *data = if_mii(ifr);
	unsigned long flags;
	int retval = 0;

	if (!netif_running(netdev))
		return -EINVAL;

	spin_lock_irqsave(&adapter->mdio_lock, flags);
	switch (cmd) {
	case SIOCGMIIPHY:
		data->phy_id = 0;
		break;

	case SIOCGMIIREG:
		if (atl1c_read_phy_reg(&adapter->hw, data->reg_num & 0x1F,
				    &data->val_out)) {
			retval = -EIO;
			goto out;
		}
		break;

	case SIOCSMIIREG:
		if (data->reg_num & ~(0x1F)) {
			retval = -EFAULT;
			goto out;
		}

		dev_dbg(&pdev->dev, "<atl1c_mii_ioctl> write %x %x",
				data->reg_num, data->val_in);
		if (atl1c_write_phy_reg(&adapter->hw,
				     data->reg_num, data->val_in)) {
			retval = -EIO;
			goto out;
		}
		break;

	default:
		retval = -EOPNOTSUPP;
		break;
	}
out:
	spin_unlock_irqrestore(&adapter->mdio_lock, flags);
	return retval;
}