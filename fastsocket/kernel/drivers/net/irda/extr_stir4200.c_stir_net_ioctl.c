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
struct stir_cb {int /*<<< orphan*/  receiving; int /*<<< orphan*/  netdev; } ;
struct net_device {int dummy; } ;
struct ifreq {int dummy; } ;
struct if_irda_req {int /*<<< orphan*/  ifr_receiving; int /*<<< orphan*/  ifr_baudrate; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
#define  SIOCGRECEIVING 130 
#define  SIOCSBANDWIDTH 129 
#define  SIOCSMEDIABUSY 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int change_speed (struct stir_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irda_device_set_media_busy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct stir_cb* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stir_net_ioctl(struct net_device *netdev, struct ifreq *rq, int cmd)
{
	struct if_irda_req *irq = (struct if_irda_req *) rq;
	struct stir_cb *stir = netdev_priv(netdev);
	int ret = 0;

	switch (cmd) {
	case SIOCSBANDWIDTH: /* Set bandwidth */
		if (!capable(CAP_NET_ADMIN))
			return -EPERM;

		/* Check if the device is still there */
		if (netif_device_present(stir->netdev))
			ret = change_speed(stir, irq->ifr_baudrate);
		break;

	case SIOCSMEDIABUSY: /* Set media busy */
		if (!capable(CAP_NET_ADMIN))
			return -EPERM;

		/* Check if the IrDA stack is still there */
		if (netif_running(stir->netdev))
			irda_device_set_media_busy(stir->netdev, TRUE);
		break;

	case SIOCGRECEIVING:
		/* Only approximately true */
		irq->ifr_receiving = stir->receiving;
		break;

	default:
		ret = -EOPNOTSUPP;
	}

	return ret;
}