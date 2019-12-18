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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct sa1100_irda {TYPE_1__ rx_buff; int /*<<< orphan*/  open; } ;
struct net_device {int dummy; } ;
struct ifreq {int dummy; } ;
struct if_irda_req {int ifr_receiving; int /*<<< orphan*/  ifr_baudrate; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  IS_FIR (struct sa1100_irda*) ; 
 int /*<<< orphan*/  OUTSIDE_FRAME ; 
#define  SIOCGRECEIVING 130 
#define  SIOCSBANDWIDTH 129 
#define  SIOCSMEDIABUSY 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irda_device_set_media_busy (struct net_device*,int /*<<< orphan*/ ) ; 
 struct sa1100_irda* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int sa1100_irda_set_speed (struct sa1100_irda*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sa1100_irda_ioctl(struct net_device *dev, struct ifreq *ifreq, int cmd)
{
	struct if_irda_req *rq = (struct if_irda_req *)ifreq;
	struct sa1100_irda *si = netdev_priv(dev);
	int ret = -EOPNOTSUPP;

	switch (cmd) {
	case SIOCSBANDWIDTH:
		if (capable(CAP_NET_ADMIN)) {
			/*
			 * We are unable to set the speed if the
			 * device is not running.
			 */
			if (si->open) {
				ret = sa1100_irda_set_speed(si,
						rq->ifr_baudrate);
			} else {
				printk("sa1100_irda_ioctl: SIOCSBANDWIDTH: !netif_running\n");
				ret = 0;
			}
		}
		break;

	case SIOCSMEDIABUSY:
		ret = -EPERM;
		if (capable(CAP_NET_ADMIN)) {
			irda_device_set_media_busy(dev, TRUE);
			ret = 0;
		}
		break;

	case SIOCGRECEIVING:
		rq->ifr_receiving = IS_FIR(si) ? 0
					: si->rx_buff.state != OUTSIDE_FRAME;
		break;

	default:
		break;
	}
		
	return ret;
}