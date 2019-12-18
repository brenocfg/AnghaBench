#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct port_info {int mdio_addr; TYPE_1__* adapter; } ;
struct net_device {int dummy; } ;
struct mii_ioctl_data {int phy_id; int reg_num; int /*<<< orphan*/  val_in; int /*<<< orphan*/  val_out; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct TYPE_3__ {unsigned int fn; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 int mdio_phy_id_devad (int) ; 
 int /*<<< orphan*/  mdio_phy_id_is_c45 (int) ; 
 int mdio_phy_id_prtad (int) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int t4_mdio_rd (TYPE_1__*,unsigned int,int,int,int,int /*<<< orphan*/ *) ; 
 int t4_mdio_wr (TYPE_1__*,unsigned int,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxgb_ioctl(struct net_device *dev, struct ifreq *req, int cmd)
{
	unsigned int mbox;
	int ret = 0, prtad, devad;
	struct port_info *pi = netdev_priv(dev);
	struct mii_ioctl_data *data = (struct mii_ioctl_data *)&req->ifr_data;

	switch (cmd) {
	case SIOCGMIIPHY:
		if (pi->mdio_addr < 0)
			return -EOPNOTSUPP;
		data->phy_id = pi->mdio_addr;
		break;
	case SIOCGMIIREG:
	case SIOCSMIIREG:
		if (mdio_phy_id_is_c45(data->phy_id)) {
			prtad = mdio_phy_id_prtad(data->phy_id);
			devad = mdio_phy_id_devad(data->phy_id);
		} else if (data->phy_id < 32) {
			prtad = data->phy_id;
			devad = 0;
			data->reg_num &= 0x1f;
		} else
			return -EINVAL;

		mbox = pi->adapter->fn;
		if (cmd == SIOCGMIIREG)
			ret = t4_mdio_rd(pi->adapter, mbox, prtad, devad,
					 data->reg_num, &data->val_out);
		else
			ret = t4_mdio_wr(pi->adapter, mbox, prtad, devad,
					 data->reg_num, data->val_in);
		break;
	default:
		return -EOPNOTSUPP;
	}
	return ret;
}