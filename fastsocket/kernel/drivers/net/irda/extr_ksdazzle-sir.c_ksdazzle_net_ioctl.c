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
struct ksdazzle_cb {int /*<<< orphan*/  receiving; int /*<<< orphan*/  netdev; } ;
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
 int /*<<< orphan*/  irda_device_set_media_busy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ksdazzle_change_speed (struct ksdazzle_cb*,int /*<<< orphan*/ ) ; 
 struct ksdazzle_cb* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ksdazzle_net_ioctl(struct net_device *netdev, struct ifreq *rq,
			      int cmd)
{
	struct if_irda_req *irq = (struct if_irda_req *)rq;
	struct ksdazzle_cb *kingsun = netdev_priv(netdev);
	int ret = 0;

	switch (cmd) {
	case SIOCSBANDWIDTH:	/* Set bandwidth */
		if (!capable(CAP_NET_ADMIN))
			return -EPERM;

		/* Check if the device is still there */
		if (netif_device_present(kingsun->netdev))
			return ksdazzle_change_speed(kingsun,
						     irq->ifr_baudrate);
		break;

	case SIOCSMEDIABUSY:	/* Set media busy */
		if (!capable(CAP_NET_ADMIN))
			return -EPERM;

		/* Check if the IrDA stack is still there */
		if (netif_running(kingsun->netdev))
			irda_device_set_media_busy(kingsun->netdev, TRUE);
		break;

	case SIOCGRECEIVING:
		/* Only approximately true */
		irq->ifr_receiving = kingsun->receiving;
		break;

	default:
		ret = -EOPNOTSUPP;
	}

	return ret;
}