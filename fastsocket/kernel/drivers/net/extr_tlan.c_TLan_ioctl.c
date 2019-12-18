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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct mii_ioctl_data {int phy_id; int reg_num; int /*<<< orphan*/  val_in; int /*<<< orphan*/  val_out; } ;
struct ifreq {int dummy; } ;
struct TYPE_3__ {int* phy; size_t phyNum; int /*<<< orphan*/  phyOnline; } ;
typedef  TYPE_1__ TLanPrivateInfo ;

/* Variables and functions */
 int EAGAIN ; 
 int EOPNOTSUPP ; 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 int /*<<< orphan*/  TLan_MiiReadReg (struct net_device*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TLan_MiiWriteReg (struct net_device*,int,int,int /*<<< orphan*/ ) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int TLan_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	TLanPrivateInfo *priv = netdev_priv(dev);
	struct mii_ioctl_data *data = if_mii(rq);
	u32 phy   = priv->phy[priv->phyNum];

	if (!priv->phyOnline)
		return -EAGAIN;

	switch(cmd) {
	case SIOCGMIIPHY:		/* Get address of MII PHY in use. */
			data->phy_id = phy;


	case SIOCGMIIREG:		/* Read MII PHY register. */
			TLan_MiiReadReg(dev, data->phy_id & 0x1f,
					data->reg_num & 0x1f, &data->val_out);
			return 0;


	case SIOCSMIIREG:		/* Write MII PHY register. */
			TLan_MiiWriteReg(dev, data->phy_id & 0x1f,
					 data->reg_num & 0x1f, data->val_in);
			return 0;
		default:
			return -EOPNOTSUPP;
	}
}