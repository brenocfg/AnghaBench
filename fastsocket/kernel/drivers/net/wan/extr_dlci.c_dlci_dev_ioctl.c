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
struct net_device {scalar_t__ dev_addr; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; int /*<<< orphan*/  ifr_slave; } ;
struct dlci_local {TYPE_1__* slave; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
#define  DLCI_GET_CONF 130 
#define  DLCI_GET_SLAVE 129 
#define  DLCI_SET_CONF 128 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int dlci_config (struct net_device*,int /*<<< orphan*/ ,int) ; 
 struct dlci_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dlci_dev_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct dlci_local *dlp;

	if (!capable(CAP_NET_ADMIN))
		return(-EPERM);

	dlp = netdev_priv(dev);

	switch(cmd)
	{
		case DLCI_GET_SLAVE:
			if (!*(short *)(dev->dev_addr))
				return(-EINVAL);

			strncpy(ifr->ifr_slave, dlp->slave->name, sizeof(ifr->ifr_slave));
			break;

		case DLCI_GET_CONF:
		case DLCI_SET_CONF:
			if (!*(short *)(dev->dev_addr))
				return(-EINVAL);

			return(dlci_config(dev, ifr->ifr_data, cmd == DLCI_GET_CONF));
			break;

		default: 
			return(-EOPNOTSUPP);
	}
	return(0);
}