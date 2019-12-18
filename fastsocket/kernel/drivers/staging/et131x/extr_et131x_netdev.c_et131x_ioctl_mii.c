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
struct net_device {int dummy; } ;
struct mii_ioctl_data {int /*<<< orphan*/  val_in; int /*<<< orphan*/  reg_num; int /*<<< orphan*/  val_out; int /*<<< orphan*/  phy_id; } ;
struct ifreq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  xcvr_addr; } ;
struct et131x_adapter {TYPE_1__ Stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int MiRead (struct et131x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MiWrite (struct et131x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 struct et131x_adapter* netdev_priv (struct net_device*) ; 

int et131x_ioctl_mii(struct net_device *netdev, struct ifreq *reqbuf, int cmd)
{
	int status = 0;
	struct et131x_adapter *etdev = netdev_priv(netdev);
	struct mii_ioctl_data *data = if_mii(reqbuf);

	switch (cmd) {
	case SIOCGMIIPHY:
		data->phy_id = etdev->Stats.xcvr_addr;
		break;

	case SIOCGMIIREG:
		if (!capable(CAP_NET_ADMIN))
			status = -EPERM;
		else
			status = MiRead(etdev,
					data->reg_num, &data->val_out);
		break;

	case SIOCSMIIREG:
		if (!capable(CAP_NET_ADMIN))
			status = -EPERM;
		else
			status = MiWrite(etdev, data->reg_num,
					 data->val_in);
		break;

	default:
		status = -EOPNOTSUPP;
	}
	return status;
}