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
struct TYPE_2__ {int /*<<< orphan*/  mdio; } ;
struct port_info {TYPE_1__ phy; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct mii_ioctl_data {int phy_id; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SIOCCHIOCTL 131 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 int cxgb_extension_ioctl (struct net_device*,int /*<<< orphan*/ ) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 int /*<<< orphan*/  is_10G (struct adapter*) ; 
 int mdio_mii_ioctl (int /*<<< orphan*/ *,struct mii_ioctl_data*,int) ; 
 int mdio_phy_id_c45 (int,int) ; 
 int /*<<< orphan*/  mdio_phy_id_is_c45 (int) ; 
 struct port_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int cxgb_ioctl(struct net_device *dev, struct ifreq *req, int cmd)
{
	struct mii_ioctl_data *data = if_mii(req);
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adapter = pi->adapter;

	switch (cmd) {
	case SIOCGMIIREG:
	case SIOCSMIIREG:
		/* Convert phy_id from older PRTAD/DEVAD format */
		if (is_10G(adapter) &&
		    !mdio_phy_id_is_c45(data->phy_id) &&
		    (data->phy_id & 0x1f00) &&
		    !(data->phy_id & 0xe0e0))
			data->phy_id = mdio_phy_id_c45(data->phy_id >> 8,
						       data->phy_id & 0x1f);
		/* FALLTHRU */
	case SIOCGMIIPHY:
		return mdio_mii_ioctl(&pi->phy.mdio, data, cmd);
	case SIOCCHIOCTL:
		return cxgb_extension_ioctl(dev, req->ifr_data);
	default:
		return -EOPNOTSUPP;
	}
}